//  :copyright: (c) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief String conversion to double.
 */

#pragma once

#include "diyfp.hpp"
#include "ieee754.hpp"


namespace lexi
{
namespace detail
{

// Take a look at the ParseNumber implementation...

//
//// Compute an approximation and see if it is within 1/2 ULP
//inline bool StrtodDiyFp(const char* decimals, size_t length, size_t decimalPosition, int exp, double* result) {
//    uint64_t significand = 0;
//    size_t i = 0;   // 2^64 - 1 = 18446744073709551615, 1844674407370955161 = 0x1999999999999999
//    for (; i < length; i++) {
//        if (significand  >  RAPIDJSON_UINT64_C2(0x19999999, 0x99999999) ||
//            (significand == RAPIDJSON_UINT64_C2(0x19999999, 0x99999999) && decimals[i] > '5'))
//            break;
//        significand = significand * 10u + static_cast<unsigned>(decimals[i] - '0');
//    }
//
//    if (i < length && decimals[i] >= '5') // Rounding
//        significand++;
//
//    size_t remaining = length - i;
//    const int kUlpShift = 3;
//    const int kUlp = 1 << kUlpShift;
//    int64_t error = (remaining == 0) ? 0 : kUlp / 2;
//
//    DiyFp v(significand, 0);
//    v = v.Normalize();
//    error <<= -v.e;
//
//    const int dExp = static_cast<int>(decimalPosition) - static_cast<int>(i) + exp;
//
//    int actualExp;
//    DiyFp cachedPower = GetCachedPower10(dExp, &actualExp);
//    if (actualExp != dExp) {
//        static const DiyFp kPow10[] = {
//            DiyFp(RAPIDJSON_UINT64_C2(0xa0000000, 00000000), -60),  // 10^1
//            DiyFp(RAPIDJSON_UINT64_C2(0xc8000000, 00000000), -57),  // 10^2
//            DiyFp(RAPIDJSON_UINT64_C2(0xfa000000, 00000000), -54),  // 10^3
//            DiyFp(RAPIDJSON_UINT64_C2(0x9c400000, 00000000), -50),  // 10^4
//            DiyFp(RAPIDJSON_UINT64_C2(0xc3500000, 00000000), -47),  // 10^5
//            DiyFp(RAPIDJSON_UINT64_C2(0xf4240000, 00000000), -44),  // 10^6
//            DiyFp(RAPIDJSON_UINT64_C2(0x98968000, 00000000), -40)   // 10^7
//        };
//        int  adjustment = dExp - actualExp - 1;
//        RAPIDJSON_ASSERT(adjustment >= 0 && adjustment < 7);
//        v = v * kPow10[adjustment];
//        if (length + static_cast<unsigned>(adjustment)> 19u) // has more digits than decimal digits in 64-bit
//            error += kUlp / 2;
//    }
//
//    v = v * cachedPower;
//
//    error += kUlp + (error == 0 ? 0 : 1);
//
//    const int oldExp = v.e;
//    v = v.Normalize();
//    error <<= oldExp - v.e;
//
//    const int effectiveSignificandSize = Double::EffectiveSignificandSize(64 + v.e);
//    int precisionSize = 64 - effectiveSignificandSize;
//    if (precisionSize + kUlpShift >= 64) {
//        int scaleExp = (precisionSize + kUlpShift) - 63;
//        v.f >>= scaleExp;
//        v.e += scaleExp;
//        error = (error >> scaleExp) + 1 + kUlp;
//        precisionSize -= scaleExp;
//    }
//
//    DiyFp rounded(v.f >> precisionSize, v.e + precisionSize);
//    const uint64_t precisionBits = (v.f & ((uint64_t(1) << precisionSize) - 1)) * kUlp;
//    const uint64_t halfWay = (uint64_t(1) << (precisionSize - 1)) * kUlp;
//    if (precisionBits >= halfWay + static_cast<unsigned>(error)) {
//        rounded.f++;
//        if (rounded.f & (DiyFp::kDpHiddenBit << 1)) { // rounding overflows mantissa (issue #340)
//            rounded.f >>= 1;
//            rounded.e++;
//        }
//    }
//
//    *result = rounded.ToDouble();
//
//    return halfWay - static_cast<unsigned>(error) >= precisionBits || precisionBits >= halfWay + static_cast<unsigned>(error);
//}
//
//inline double StrtodBigInteger(double approx, const char* decimals, size_t length, size_t decimalPosition, int exp) {
//    const BigInteger dInt(decimals, length);
//    const int dExp = static_cast<int>(decimalPosition) - static_cast<int>(length) + exp;
//    Double a(approx);
//    int cmp = withinHalfULP(a.Value(), dInt, dExp);
//    if (cmp < 0)
//        return a.Value();  // within half ULP
//    else if (cmp == 0) {
//        // Round towards even
//        if (a.Significand() & 1)
//            return a.NextPositiveDouble();
//        else
//            return a.Value();
//    }
//    else // adjustment
//        return a.NextPositiveDouble();
//}
//
//inline double StrtodFullPrecision(double d, int p, const char* decimals, size_t length, size_t decimalPosition, int exp) {
//    RAPIDJSON_ASSERT(d >= 0.0);
//    RAPIDJSON_ASSERT(length >= 1);
//
//    double result;
//    if (fast(d, p, &result)) {
//        return result;
//    }
//
//    // Trim leading zeros
//    while (*decimals == '0' && length > 1) {
//        length--;
//        decimals++;
//        decimalPosition--;
//    }
//
//    // Trim trailing zeros
//    while (decimals[length - 1] == '0' && length > 1) {
//        length--;
//        decimalPosition--;
//        exp++;
//    }
//
//    // Trim right-most digits
//    const int kMaxDecimalDigit = 780;
//    if (static_cast<int>(length) > kMaxDecimalDigit) {
//        int delta = (static_cast<int>(length) - kMaxDecimalDigit);
//        exp += delta;
//        decimalPosition -= static_cast<unsigned>(delta);
//        length = kMaxDecimalDigit;
//    }
//
//    // If too small, underflow to zero
//    if (int(length) + exp < -324)
//        return 0.0;
//
//    if (StrtodDiyFp(decimals, length, decimalPosition, exp, &result))
//        return result;
//
//    // Use approximation from StrtodDiyFp and make adjustment with BigInteger comparison
//    return StrtodBigInteger(result, decimals, length, decimalPosition, exp);
//}



}   /* detail */
}   /* lexi */
