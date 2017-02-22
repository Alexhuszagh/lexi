//  :copyright: (c) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief String conversion to double.
 */

#include "lexi/detail/bigint.hpp"
#include "lexi/detail/strtod.hpp"
#include "lexi/detail/pow.hpp"

#include <algorithm>


namespace lexi
{
namespace detail
{
// FUNCTIONS -- HELPERS
// --------------------


/** \brief Fast exponent calculation.
 */
static double fastPath(double significand,
    int exp)
{
    if (exp < -308) {
        return 0.0;
    } else if (exp >= 0) {
        return significand * pow10(exp);
    } else {
        return significand / pow10(-exp);
    }
}


/** \brief Fast method to raise number to exponent.
 */
static double StrtodNormalPrecision(double d,
    int p)
{
    if (p < -308) {
        // Prevent expSum < -308, making pow10(p) = 0
        d = fastPath(d, -308);
        d = fastPath(d, p + 308);
    } else {
        d = fastPath(d, p);
    }
    return d;
}


/** \brief std::min implementation for 3 variables
 */
template <typename T>
static T min3(T a,
    T b,
    T c)
{
    return std::min<T>(a, std::min<T>(b, c));
}


static int withinHalfULP(double b,
    const BigInteger &d,
    int dExp)
{
    // TODO: implement
    return 0;

//    const Double db(b);
//    const uint64_t bInt = db.IntegerSignificand();
//    const int bExp = db.IntegerExponent();
//    const int hExp = bExp - 1;
//
//    int dS_Exp2 = 0, dS_Exp5 = 0, bS_Exp2 = 0, bS_Exp5 = 0, hS_Exp2 = 0, hS_Exp5 = 0;
//
//    // Adjust for decimal exponent
//    if (dExp >= 0) {
//        dS_Exp2 += dExp;
//        dS_Exp5 += dExp;
//    }
//    else {
//        bS_Exp2 -= dExp;
//        bS_Exp5 -= dExp;
//        hS_Exp2 -= dExp;
//        hS_Exp5 -= dExp;
//    }
//
//    // Adjust for binary exponent
//    if (bExp >= 0)
//        bS_Exp2 += bExp;
//    else {
//        dS_Exp2 -= bExp;
//        hS_Exp2 -= bExp;
//    }
//
//    // Adjust for half ulp exponent
//    if (hExp >= 0)
//        hS_Exp2 += hExp;
//    else {
//        dS_Exp2 -= hExp;
//        bS_Exp2 -= hExp;
//    }
//
//    // Remove common power of two factor from all three scaled values
//    int common_Exp2 = min3(dS_Exp2, bS_Exp2, hS_Exp2);
//    dS_Exp2 -= common_Exp2;
//    bS_Exp2 -= common_Exp2;
//    hS_Exp2 -= common_Exp2;
//
//    BigInteger dS = d;
//    dS.MultiplyPow5(static_cast<unsigned>(dS_Exp5)) <<= static_cast<unsigned>(dS_Exp2);
//
//    BigInteger bS(bInt);
//    bS.MultiplyPow5(static_cast<unsigned>(bS_Exp5)) <<= static_cast<unsigned>(bS_Exp2);
//
//    BigInteger hS(1);
//    hS.MultiplyPow5(static_cast<unsigned>(hS_Exp5)) <<= static_cast<unsigned>(hS_Exp2);
//
//    BigInteger delta(0);
//    dS.Difference(bS, &delta);
//
//    return delta.compare(hS);
}


// FUNCTIONS -- STRTOD
// -------------------


/** \brief Fast path for string-to-double conversion if possible.
 *
 *  \reference http://www.exploringbinary.com/fast-path-decimal-to-floating-point-conversion/
 */
static bool fast(double d, int p, double *result)
{
    if (p > 22  && p < 22 + 16) {
        // Fast Path Cases In Disguise
        d *= pow10(p - 22);
        p = 22;
    }

    if (p >= -22 && p <= 22 && d <= 9007199254740991.0) { // 2^53 - 1
        *result = fastPath(d, p);
        return true;
    } else {
        return false;
    }
}

}   /* detail */
}   /* lexi */
