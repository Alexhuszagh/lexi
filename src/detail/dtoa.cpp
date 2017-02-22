//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Double conversion to strings.
 */

#include "lexi/detail/dtoa.hpp"

#include <cstring>


namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

static const char DIGITS[200] = {
    '0', '0', '0', '1', '0', '2', '0', '3', '0', '4', '0', '5', '0', '6', '0', '7', '0', '8', '0', '9',
    '1', '0', '1', '1', '1', '2', '1', '3', '1', '4', '1', '5', '1', '6', '1', '7', '1', '8', '1', '9',
    '2', '0', '2', '1', '2', '2', '2', '3', '2', '4', '2', '5', '2', '6', '2', '7', '2', '8', '2', '9',
    '3', '0', '3', '1', '3', '2', '3', '3', '3', '4', '3', '5', '3', '6', '3', '7', '3', '8', '3', '9',
    '4', '0', '4', '1', '4', '2', '4', '3', '4', '4', '4', '5', '4', '6', '4', '7', '4', '8', '4', '9',
    '5', '0', '5', '1', '5', '2', '5', '3', '5', '4', '5', '5', '5', '6', '5', '7', '5', '8', '5', '9',
    '6', '0', '6', '1', '6', '2', '6', '3', '6', '4', '6', '5', '6', '6', '6', '7', '6', '8', '6', '9',
    '7', '0', '7', '1', '7', '2', '7', '3', '7', '4', '7', '5', '7', '6', '7', '7', '7', '8', '7', '9',
    '8', '0', '8', '1', '8', '2', '8', '3', '8', '4', '8', '5', '8', '6', '8', '7', '8', '8', '8', '9',
    '9', '0', '9', '1', '9', '2', '9', '3', '9', '4', '9', '5', '9', '6', '9', '7', '9', '8', '9', '9'
};
static const char *DIGITS_PTR = DIGITS;
static const uint32_t POWER10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
static const uint64_t CACHED_POWERS_F[] = {
    0XFA8FD5A0081C0288ULL,
    0XBAAEE17FA23EBF76ULL,
    0X8B16FB203055AC76ULL,
    0XCF42894A5DCE35EAULL,
    0X9A6BB0AA55653B2DULL,
    0XE61ACF033D1A45DFULL,
    0XAB70FE17C79AC6CAULL,
    0XFF77B1FCBEBCDC4FULL,
    0XBE5691EF416BD60CULL,
    0X8DD01FAD907FFC3CULL,
    0XD3515C2831559A83ULL,
    0X9D71AC8FADA6C9B5ULL,
    0XEA9C227723EE8BCBULL,
    0XAECC49914078536DULL,
    0X823C12795DB6CE57ULL,
    0XC21094364DFB5637ULL,
    0X9096EA6F3848984FULL,
    0XD77485CB25823AC7ULL,
    0XA086CFCD97BF97F4ULL,
    0XEF340A98172AACE5ULL,
    0XB23867FB2A35B28EULL,
    0X84C8D4DFD2C63F3BULL,
    0XC5DD44271AD3CDBAULL,
    0X936B9FCEBB25C996ULL,
    0XDBAC6C247D62A584ULL,
    0XA3AB66580D5FDAF6ULL,
    0XF3E2F893DEC3F126ULL,
    0XB5B5ADA8AAFF80B8ULL,
    0X87625F056C7C4A8BULL,
    0XC9BCFF6034C13053ULL,
    0X964E858C91BA2655ULL,
    0XDFF9772470297EBDULL,
    0XA6DFBD9FB8E5B88FULL,
    0XF8A95FCF88747D94ULL,
    0XB94470938FA89BCFULL,
    0X8A08F0F8BF0F156BULL,
    0XCDB02555653131B6ULL,
    0X993FE2C6D07B7FACULL,
    0XE45C10C42A2B3B06ULL,
    0XAA242499697392D3ULL,
    0XFD87B5F28300CA0EULL,
    0XBCE5086492111AEBULL,
    0X8CBCCC096F5088CCULL,
    0XD1B71758E219652CULL,
    0X9C40000000000000ULL,
    0XE8D4A51000000000ULL,
    0XAD78EBC5AC620000ULL,
    0X813F3978F8940984ULL,
    0XC097CE7BC90715B3ULL,
    0X8F7E32CE7BEA5C70ULL,
    0XD5D238A4ABE98068ULL,
    0X9F4F2726179A2245ULL,
    0XED63A231D4C4FB27ULL,
    0XB0DE65388CC8ADA8ULL,
    0X83C7088E1AAB65DBULL,
    0XC45D1DF942711D9AULL,
    0X924D692CA61BE758ULL,
    0XDA01EE641A708DEAULL,
    0XA26DA3999AEF774AULL,
    0XF209787BB47D6B85ULL,
    0XB454E4A179DD1877ULL,
    0X865B86925B9BC5C2ULL,
    0XC83553C5C8965D3DULL,
    0X952AB45CFA97A0B3ULL,
    0XDE469FBD99A05FE3ULL,
    0XA59BC234DB398C25ULL,
    0XF6C69A72A3989F5CULL,
    0XB7DCBF5354E9BECEULL,
    0X88FCF317F22241E2ULL,
    0XCC20CE9BD35C78A5ULL,
    0X98165AF37B2153DFULL,
    0XE2A0B5DC971F303AULL,
    0XA8D9D1535CE3B396ULL,
    0XFB9B7CD9A4A7443CULL,
    0XBB764C4CA7A44410ULL,
    0X8BAB8EEFB6409C1AULL,
    0XD01FEF10A657842CULL,
    0X9B10A4E5E9913129ULL,
    0XE7109BFBA19C0C9DULL,
    0XAC2820D9623BF429ULL,
    0X80444B5E7AA7CF85ULL,
    0XBF21E44003ACDD2DULL,
    0X8E679C2F5E44FF8FULL,
    0XD433179D9C8CB841ULL,
    0X9E19DB92B4E31BA9ULL,
    0XEB96BF6EBADF77D9ULL,
    0XAF87023B9BF0EE6BULL,
};

static const int16_t CACHED_POWERS_E[] = {
    -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007,  -980,
     -954,  -927,  -901,  -874,  -847,  -821,  -794,  -768,  -741,  -715,
     -688,  -661,  -635,  -608,  -582,  -555,  -529,  -502,  -475,  -449,
     -422,  -396,  -369,  -343,  -316,  -289,  -263,  -236,  -210,  -183,
     -157,  -130,  -103,   -77,   -50,   -24,     3,    30,    56,    83,
      109,   136,   162,   189,   216,   242,   269,   295,   322,   348,
      375,   402,   428,   455,   481,   508,   534,   561,   588,   614,
      641,   667,   694,   720,   747,   774,   800,   827,   853,   880,
      907,   933,   960,   986,  1013,  1039,  1066
};

// MACROS
// ------

#if defined(_MSC_VER)
#   define LEXI_UNREACHABLE(d) __assume(0)
#elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#   define LEXI_UNREACHABLE(d) __builtin_unreachable()
#else
#   define LEXI_UNREACHABLE(d) d = 0
#endif          // MSC_VER

// FUNCTIONS
// ---------


/** \brief Round digit count from Grisu2 value.
 */
void grisuRound(char *buffer,
    int len,
    uint64_t delta,
    uint64_t rest,
    uint64_t ten_kappa,
    uint64_t wp_w)
{
    while (rest < wp_w && delta - rest >= ten_kappa &&
           (rest + ten_kappa < wp_w ||  /// closer
            wp_w - rest > rest + ten_kappa - wp_w)) {
        buffer[len - 1]--;
        rest += ten_kappa;
    }
}


/** \brief Count the number of decimal digits.
 *
 *  Simple pure C++ implementation was faster than __builtin_clz version
 *  in this situation.
 */
unsigned int decimalCount(uint32_t n)
{
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}


/** \brief Get the cached power.
 */
DiyFp getCachedPower(int e,
    int *k)
{
    //int k = static_cast<int>(ceil((-61 - e) * 0.30102999566398114)) + 374;
    double dk = (-61 - e) * 0.30102999566398114 + 347;
    // dk must be positive, so can do ceiling in positive
    int kk = static_cast<int>(dk);
    if (kk != dk) {
        kk++;
    }

    unsigned index = static_cast<unsigned>((kk >> 3) + 1);
    // decimal exponent no need lookup table
    *k = -(-348 + static_cast<int>(index << 3));

    return DiyFp(CACHED_POWERS_F[index], CACHED_POWERS_E[index]);
}


/** \brief Generate digits and move into buffer.
 */
void generateDigits(const DiyFp &W,
    const DiyFp &Mp,
    uint64_t delta,
    char *buffer,
    int *len,
    int *k)
{
    const DiyFp one(uint64_t(1) << -Mp.e, Mp.e);
    const DiyFp wp_w = Mp - W;
    uint32_t p1 = static_cast<uint32_t>(Mp.f >> -one.e);
    uint64_t p2 = Mp.f & (one.f - 1);
    int kappa = static_cast<int>(decimalCount(p1));
    *len = 0;

    while (kappa > 0) {
        uint32_t d;
        switch (kappa) {
            case 10: d = p1 / 1000000000; p1 %= 1000000000; break;
            case  9: d = p1 /  100000000; p1 %=  100000000; break;
            case  8: d = p1 /   10000000; p1 %=   10000000; break;
            case  7: d = p1 /    1000000; p1 %=    1000000; break;
            case  6: d = p1 /     100000; p1 %=     100000; break;
            case  5: d = p1 /      10000; p1 %=      10000; break;
            case  4: d = p1 /       1000; p1 %=       1000; break;
            case  3: d = p1 /        100; p1 %=        100; break;
            case  2: d = p1 /         10; p1 %=         10; break;
            case  1: d = p1;              p1 =           0; break;
            default:
                LEXI_UNREACHABLE(d);
        }
        if (d || *len) {
            buffer[(*len)++] = '0' + static_cast<char>(d);
        }
        kappa--;
        uint64_t tmp = (static_cast<uint64_t>(p1) << -one.e) + p2;
        if (tmp <= delta) {
            *k += kappa;
            grisuRound(buffer, *len, delta, tmp, static_cast<uint64_t>(POWER10[kappa]) << -one.e, wp_w.f);
            return;
        }
    }

    // kappa = 0
    for (;;) {
        p2 *= 10;
        delta *= 10;
        char d = static_cast<char>(p2 >> -one.e);
        if (d || *len) {
            buffer[(*len)++] = '0' + d;
        }
        p2 &= one.f - 1;
        kappa--;
        if (p2 < delta) {
            *k += kappa;
            grisuRound(buffer, *len, delta, p2, one.f, wp_w.f * POWER10[-kappa]);
            return;
        }
    }
}


/** \brief Core Grisu2 algorithm.
 */
void grisu2(double value,
    char *buffer,
    int *length,
    int *k)
{
    const DiyFp v(value);
    DiyFp w_m, w_p;
    v.normalizedBoundaries(&w_m, &w_p);

    const DiyFp c_mk = getCachedPower(w_p.e, k);
    const DiyFp W = v.normalize() * c_mk;
    DiyFp Wp = w_p * c_mk;
    DiyFp Wm = w_m * c_mk;
    Wm.f++;
    Wp.f--;
    generateDigits(W, Wp, Wp.f - Wm.f, buffer, length, k);
}


/** \brief Write exponent section to buffer.
 */
inline char * writeExponent(int k,
    char *buffer)
{
    if (k < 0) {
        *buffer++ = '-';
        k = -k;
    }

    if (k >= 100) {
        *buffer++ = '0' + static_cast<char>(k / 100);
        k %= 100;
        const char *d = DIGITS_PTR + k * 2;
        *buffer++ = d[0];
        *buffer++ = d[1];
    } else if (k >= 10) {
        const char *d = DIGITS_PTR + k * 2;
        *buffer++ = d[0];
        *buffer++ = d[1];
    } else {
        *buffer++ = '0' + static_cast<char>(k);
    }
    *buffer = '\0';

    return buffer;
}


/** \brief Format buffer to prettify float output.
 */
char * prettify(char *buffer,
    int length,
    int k)
{
    const int kk = length + k;  // 10^(kk-1) <= v < 10^kk

    if (length <= kk && kk <= 21) {
        // 1234e7 -> 12340000000
        for (int i = length; i < kk; i++) {
            buffer[i] = '0';
        }
        buffer[kk] = '.';
        buffer[kk + 1] = '0';
        buffer[kk + 2] = '\0';
        return &buffer[kk + 2];
    } else if (0 < kk && kk <= 21) {
        // 1234e-2 -> 12.34
        memmove(&buffer[kk + 1], &buffer[kk], length - kk);
        buffer[kk] = '.';
        buffer[length + 1] = '\0';
        return &buffer[length + 1];
    }
    else if (-6 < kk && kk <= 0) {
        // 1234e-6 -> 0.001234
        const int offset = 2 - kk;
        memmove(&buffer[offset], &buffer[0], length);
        buffer[0] = '0';
        buffer[1] = '.';
        for (int i = 2; i < offset; i++) {
            buffer[i] = '0';
        }
        buffer[length + offset] = '\0';
        return &buffer[length + offset];
    } else if (length == 1) {
        // 1e30
        buffer[1] = 'e';
        return writeExponent(kk - 1, &buffer[2]);
    } else {
        // 1234e30 -> 1.234e33
        memmove(&buffer[2], &buffer[1], length - 1);
        buffer[1] = '.';
        buffer[length + 1] = 'e';
        return writeExponent(kk - 1, &buffer[0 + length + 2]);
    }
}


/** \brief Format finite double to string buffer.
 */
char * dtoa(double value,
    char *buffer)
{
    if (value == 0) {
        *buffer++ = '0';
        *buffer++ = '.';
        *buffer++ = '0';
        *buffer = '\0';
    } else {
        if (value < 0) {
            *buffer++ = '-';
            value = -value;
        }
        int length, k;
        grisu2(value, buffer, &length, &k);
        buffer = prettify(buffer, length, k);
    }

    return buffer;
}

}   /* detail */
}   /* lexi */
