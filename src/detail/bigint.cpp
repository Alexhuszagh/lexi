//  :copyright: (c) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Big integer representation.
 */

#include "lexi/detail/bigint.hpp"
#include "lexi/detail/define.hpp"

#if defined(_MSC_VER) && defined(_M_AMD64)
#   include <intrin.h>
#   pragma intrinsic(_umul128)
#endif

#include <cstring>


namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

// 2^64 = 18446744073709551616 > 10^19
static constexpr size_t DIGITS_ITERATION = 19;
static constexpr size_t INT64_BYTE = sizeof(uint64_t) * 8;
static const uint32_t POWER5[12] = {
    5,
    5 * 5,
    5 * 5 * 5,
    5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
    5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5
};

// FUNCTIONS
// ---------


// MULTIPLY & ADD

#if defined(_MSC_VER) && defined(_M_AMD64)

    /** \brief Specialized implementation for 64-bit Windows.
     */
    static uint64_t mulAdd(uint64_t a,
        uint64_t b,
        uint64_t k,
        uint64_t *outHigh)
    {
        uint64_t low = _umul128(a, b, outHigh) + k;
        if (low < k)
            (*outHigh)++;
        return low;
    }

#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__x86_64__)

    /** \brief Specialized implementation for 64-bit GNUC 4+.
     */
    static uint64_t mulAdd(uint64_t a,
        uint64_t b,
        uint64_t k,
        uint64_t *outHigh)
    {
        __extension__ typedef unsigned __int128 uint128;
        uint128 p = static_cast<uint128>(a) * static_cast<uint128>(b);
        p += k;
        *outHigh = static_cast<uint64_t>(p >> 64);
        return static_cast<uint64_t>(p);
    }

#else

    /** \brief Generalized implementation for other compilers.
     */
    static uint64_t mulAdd(uint64_t a,
        uint64_t b,
        uint64_t k,
        uint64_t *outHigh)
    {
        const uint64_t a0 = a & 0xFFFFFFFF, a1 = a >> 32, b0 = b & 0xFFFFFFFF, b1 = b >> 32;
        uint64_t x0 = a0 * b0, x1 = a0 * b1, x2 = a1 * b0, x3 = a1 * b1;
        x1 += (x0 >> 32); // can't give carry
        x1 += x2;
        if (x1 < x2) {
            x3 += (static_cast<uint64_t>(1) << 32);
        }
        uint64_t lo = (x1 << 32) + (x0 & 0xFFFFFFFF);
        uint64_t hi = x3 + (x1 >> 32);

        lo += k;
        if (lo < k) {
            hi++;
        }
        *outHigh = hi;
        return lo;
    }

#endif


// OBJECTS
// -------


/** \brief Add 64-bit decimal to integer.
 */
void BigInteger::add(const char *first,
    const char *last)
{
    uint64_t digit = parse(first, last);
    if (isZero()) {
        *this = digit;
    } else {
        unsigned int exp = static_cast<unsigned int>(last - first);
        (mulPow5(exp) <<= exp) += digit;
    }
}


/** \brief Push back 64-bit decimal in buffer.
 */
void BigInteger::push_back(uint64_t digit)
{
    LEXI_ASSERT(count_ < capacity);
    digits_[count_++] = digit;
}


/** \brief Parse single integer from range.
 */
uint64_t BigInteger::parse(const char *first,
    const char *last)
{
    uint64_t r = 0;
    for (const char *p = first; p != last; ++p) {
        LEXI_ASSERT(*p >= '0' && *p <= '9');
        r = r * 10u + static_cast<unsigned>(*p - '0');
    }
    return r;
}


/** \brief Copy constructor.
 */
BigInteger::BigInteger(const BigInteger &other):
    count_(other.count_)
{
    memcpy(digits_, other.digits_, count_ * sizeof(uint64_t));
}


/** \brief Copy assignment operator.
 */
BigInteger & BigInteger::operator=(const BigInteger &other)
{
    if (this != &other) {
        count_ = other.count_;
        memcpy(digits_, other.digits_, count_ * sizeof(uint64_t));
    }
    return *this;
}


/** \brief Initialize single digit.
 */
BigInteger::BigInteger(uint64_t digit):
    count_(1)
{
    digits_[0] = digit;
}


/** \brief Assign single digit.
 */
BigInteger & BigInteger::operator=(uint64_t digit)
{
    digits_[0] = digit;
    count_ = 1;
    return *this;
}


/** \brief Initialize from existing buffer.
 */
BigInteger::BigInteger(const char* decimals,
        size_t length):
    count_(1)
{
    digits_[0] = 0;
    size_t i = 0;
    while (length >= DIGITS_ITERATION) {
        add(decimals + i, decimals + i + DIGITS_ITERATION);
        length -= DIGITS_ITERATION;
        i += DIGITS_ITERATION;
    }

    if (length > 0) {
        add(decimals + i, decimals + i + length);
    }
}


/** \brief Count property.
 */
size_t BigInteger::count() const
{
    return count_;
}


/** \brief Get digit at index.
 */
uint64_t BigInteger::digit(size_t index) const
{
    LEXI_ASSERT(index < count_);
    return digits_[index];
}


/** \brief Check if value is 0.
 */
bool BigInteger::isZero() const
{
    return count_ == 1 && digits_[0] == 0;
}


/** \brief In-place addition operator.
 */
BigInteger & BigInteger::operator+=(uint64_t digit)
{
    uint64_t backup = digits_[0];
    digits_[0] += digit;
    for (size_t i = 0; i < count_ - 1; i++) {
        if (digits_[i] >= backup) {
            return *this; // no carry
        }
        backup = digits_[i + 1];
        digits_[i + 1] += 1;
    }

    // Last carry
    if (digits_[count_ - 1] < backup) {
        push_back(1);
    }

    return *this;
}


/** \brief In-place multiplication operator.
 */
BigInteger & BigInteger::operator*=(uint64_t digit)
{
    if (digit == 0) {
        return *this = 0;
    } else if (digit == 1) {
        return *this;
    } else if (*this == 1) {
        return *this = digit;
    }

    uint64_t k = 0;
    for (size_t i = 0; i < count_; i++) {
        uint64_t hi;
        digits_[i] = mulAdd(digits_[i], digit, k, &hi);
        k = hi;
    }

    if (k > 0) {
        push_back(k);
    }

    return *this;
}


/** \brief In-place multiplication operator.
 */
BigInteger & BigInteger::operator*=(uint32_t digit)
{
    if (digit == 0) {
        return *this = 0;
    } else if (digit == 1) {
        return *this;
    } else if (*this == 1) {
        return *this = digit;
    }

    uint64_t k = 0;
    for (size_t i = 0; i < count_; i++) {
        const uint64_t c = digits_[i] >> 32;
        const uint64_t d = digits_[i] & 0xFFFFFFFF;
        const uint64_t uc = digit * c;
        const uint64_t ud = digit * d;
        const uint64_t p0 = ud + k;
        const uint64_t p1 = uc + (p0 >> 32);
        digits_[i] = (p0 & 0xFFFFFFFF) | (p1 << 32);
        k = p1 >> 32;
    }

    if (k > 0) {
        push_back(k);
    }

    return *this;
}


/** \brief Bitwise shift operator.
 */
BigInteger & BigInteger::operator<<=(size_t shift)
{
    if (isZero() || shift == 0) {
        return *this;
    }

    size_t offset = shift / INT64_BYTE;
    size_t interShift = shift % INT64_BYTE;
    LEXI_ASSERT(count_ + offset <= capacity);

    if (interShift == 0) {
        memmove(&digits_[count_ - 1 + offset], &digits_[count_ - 1], count_ * sizeof(uint64_t));
        count_ += offset;
    }
    else {
        digits_[count_] = 0;
        for (size_t i = count_; i > 0; i--) {
            digits_[i + offset] = (digits_[i] << interShift) | (digits_[i - 1] >> (INT64_BYTE - interShift));
        }
        digits_[offset] = digits_[0] << interShift;
        count_ += offset;
        if (digits_[count_]) {
            count_++;
        }
    }

    memset(digits_, 0, offset * sizeof(uint64_t));

    return *this;
}


/** \brief Equality operator.
 */
bool BigInteger::operator==(const BigInteger &other) const
{
    return count_ == other.count_ && memcmp(digits_, other.digits_, count_ * sizeof(uint64_t)) == 0;
}


/** \brief Equality operator.
 */
bool BigInteger::operator==(const uint64_t other) const
{
    return count_ == 1 && digits_[0] == other;
}


/** \brief Multiply by a power of 5.
 */
BigInteger & BigInteger::mulPow5(unsigned int exponent)
{
    if (exponent == 0) {
        return *this;
    }
    for (; exponent >= 27; exponent -= 27) {
        *this *= static_cast<uint64_t>(0X6765C793FA10079DULL);  // 5^27
    }
    for (; exponent >= 13; exponent -= 13) {
        *this *= static_cast<uint32_t>(1220703125u);            // 5^13
    }
    if (exponent > 0) {
        *this *= POWER5[exponent - 1];
    }
    return *this;
}


/** \brief Compute absolute difference of this and other.
 */
bool BigInteger::difference(const BigInteger &other,
    BigInteger *out) const
{
    int cmp = compare(other);
    LEXI_ASSERT(cmp != 0);

    const BigInteger *a, *b;  // Makes a > b
    bool ret;
    if (cmp < 0) {
        a = &other; b = this;
        ret = true;
    } else {
        a = this; b = &other;
        ret = false;
    }

    uint64_t borrow = 0;
    for (size_t i = 0; i < a->count_; i++) {
        uint64_t d = a->digits_[i] - borrow;
        if (i < b->count_) {
            d -= b->digits_[i];
        }
        borrow = (d > a->digits_[i]) ? 1 : 0;
        out->digits_[i] = d;
        if (d != 0) {
            out->count_ = i + 1;
        }
    }

    return ret;
}


/** \brief Compare difference between this and other.
 */
int BigInteger::compare(const BigInteger &other) const
{
    if (count_ != other.count_) {
        return count_ < other.count_ ? -1 : 1;
    }

    for (size_t i = count_; i-- > 0;)
        if (digits_[i] != other.digits_[i]) {
            return digits_[i] < other.digits_[i] ? -1 : 1;
        }

    return 0;
}

}   /* detail */
}   /* lexi */
