//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Double conversion to strings.
 */

#include "lexi/detail/diyfp.hpp"
#include "lexi/detail/ieee754.hpp"

#ifdef _MSC_VER
#   include <intrin.h>
#endif

#include <cmath>


namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

static constexpr int DIY_SIGNIFICAND_SIZE = 64;
static constexpr int DP_SIGNIFICAND_SIZE = 52;
static constexpr int DP_EXPONENT_BIAS = 0x3FF + DP_SIGNIFICAND_SIZE;
static constexpr int DP_MIN_EXPONENT = -DP_EXPONENT_BIAS;
static constexpr uint64_t HIDDEN_BIT = 0X0010000000000000ULL;

// FUNCTIONS
// ---------

// MULTIPLY

#if defined(_MSC_VER) && defined(_M_AMD64)

    /** \brief Optimized multiplication for MSVC64.
     */
    DiyFp mul(const DiyFp &left,
        const DiyFp &right)
    {
        uint64_t h;
        uint64_t l = _umul128(left.f, right.f, &h);
        if (l & (uint64_t(1) << 63)) { // rounding
            h++;
        }
        return DiyFp(h, left.e + right.e + 64);
    }

#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__x86_64__)

    /** \brief Optimized multiplication for GNUC 4+.
     */
    DiyFp mul(const DiyFp &left,
        const DiyFp &right)
    {
        unsigned __int128 p = static_cast<unsigned __int128>(left.f) * static_cast<unsigned __int128>(right.f);
        uint64_t h = p >> 64;
        uint64_t l = static_cast<uint64_t>(p);
        if (l & (uint64_t(1) << 63)) { // rounding
            h++;
        }
        return DiyFp(h, left.e + right.e + 64);
    }

#else

    /** \brief Generalized multiplication for other compilers.
     */
    DiyFp mul(const DiyFp &left,
        const DiyFp &right)
    {
        const uint64_t M32 = 0xFFFFFFFF;
        const uint64_t a = left.f >> 32;
        const uint64_t b = left.f & M32;
        const uint64_t c = right.f >> 32;
        const uint64_t d = right.f & M32;
        const uint64_t ac = a * c;
        const uint64_t bc = b * c;
        const uint64_t ad = a * d;
        const uint64_t bd = b * d;
        uint64_t tmp = (bd >> 32) + (ad & M32) + (bc & M32);
        tmp += 1U << 31;  /// mult_round
        return DiyFp(ac + (ad >> 32) + (bc >> 32) + (tmp >> 32), left.e + right.e + 64);
    }

#endif          // MULTIPLY

// NORMALIZE

#if defined(_MSC_VER) && defined(_M_AMD64)

    /** \brief Normalize specialized for MSVC.
     */
    DiyFp normalize(const DiyFp &diyfp)
    {
        unsigned long index;
        _BitScanReverse64(&index, diyfp.f);
        return DiyFp(diyfp.f << (63 - index), diyfp.e - (63 - index));
    }

#elif defined(__GNUC__)

    /** \brief Normalize specialized for GNUC.
     */
    DiyFp normalize(const DiyFp &diyfp)
    {
        int s = __builtin_clzll(diyfp.f);
        return DiyFp(diyfp.f << s, diyfp.e - s);
    }
#else

    /** \brief Generalized normalization for other compilers.
     */
    DiyFp normalize(const DiyFp &diyfp)
    {
        DiyFp res = diyfp;
        while (!(res.f & HIDDEN_BIT)) {
            res.f <<= 1;
            res.e--;
        }
        res.f <<= (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 1);
        res.e = res.e - (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 1);
        return res;
    }

#endif          // NORMALIZE

// NORMALIZE BOUNDARY

#if defined(_MSC_VER) && defined(_M_AMD64)

    /** \brief Normalize boundary specialized for MSVC.
     */
    DiyFp normalizeBoundary(const DiyFp &diyfp)
    {
        unsigned long index;
        _BitScanReverse64(&index, diyfp.f);
        return DiyFp(diyfp.f << (63 - index), diyfp.e - (63 - index));
    }

#else

    /** \brief Generalized normalization for other compilers.
     */
    DiyFp normalizeBoundary(const DiyFp &diyfp)
    {
        DiyFp res = diyfp;
        while (!(res.f & (HIDDEN_BIT << 1))) {
            res.f <<= 1;
            res.e--;
        }
        res.f <<= (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 2);
        res.e = res.e - (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 2);
        return res;
    }

#endif          // NORMALIZE BOUNDARY

// OBJECTS
// -------


/** \brief Null constructor.
 */
DiyFp::DiyFp():
    f(),
    e()
{}


/** \brief Initializer constructor.
 */
DiyFp::DiyFp(uint64_t f, int e):
    f(f),
    e(e)
{}


DiyFp::DiyFp(double d)
{
    BitwiseDouble u = {d};

    int biased_e = (u.u64 & EXPONENT_MASK) >> DP_SIGNIFICAND_SIZE;
    uint64_t significand = (u.u64 & SIGNIFICAND_MASK);
    if (biased_e != 0) {
        f = significand + HIDDEN_BIT;
        e = biased_e - DP_EXPONENT_BIAS;
    }
    else {
        f = significand;
        e = DP_MIN_EXPONENT + 1;
    }
}


/** \brief Subtraction operator.
 */
DiyFp DiyFp::operator-(const DiyFp &other) const
{
    return DiyFp(f - other.f, e);
}


DiyFp DiyFp::operator*(const DiyFp& rhs) const
{
    return mul(*this, rhs);
}


DiyFp DiyFp::normalize() const
{
    return detail::normalize(*this);
}


DiyFp DiyFp::normalizeBoundary() const
{
    return detail::normalizeBoundary(*this);
}


void DiyFp::normalizedBoundaries(DiyFp *minus, DiyFp *plus) const
{
    DiyFp pl = DiyFp((f << 1) + 1, e - 1).normalizeBoundary();
    DiyFp mi = (f == HIDDEN_BIT) ? DiyFp((f << 2) - 1, e - 2) : DiyFp((f << 1) - 1, e - 1);
    mi.f <<= mi.e - pl.e;
    mi.e = pl.e;
    *plus = pl;
    *minus = mi;
}

}   /* detail */
}   /* lexi */
