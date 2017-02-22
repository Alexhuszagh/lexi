//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup JSON
 *  \brief Floating point number specifications.
 */

#include "lexi/detail/ieee754.hpp"


namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

static const uint64_t INFINITY = 0x7FF0000000000000ULL;
static const uint64_t NEGATIVE_INFINITY = 0xFFF0000000000000;

// FUNCTIONS
// ---------


/** \brief Check if number is NaN.
 */
bool isNan(const double number)
{
    BitwiseDouble u = {number};
    return !isFinite(number) && ((u.u64 & SIGNIFICAND_MASK) != 0);
}


/** \brief Check if number is inf.
 */
bool isInf(const double number)
{
    BitwiseDouble u = {number};
    return !isFinite(number) && ((u.u64 & SIGNIFICAND_MASK) == 0);
}


/** \brief Check if number is -inf.
 */
bool isNegativeInfinity(const double number)
{
    BitwiseDouble u = {number};
    return u.u64 == NEGATIVE_INFINITY;
}


/** \brief Check if number is inf.
 */
bool isInfinity(const double number)
{
    BitwiseDouble u = {number};
    return u.u64 == INFINITY;
}


/** \brief Check if number is not NaN or inf.
 */
bool isFinite(const double number)
{
    BitwiseDouble u = {number};
    return (u.u64 & EXPONENT_MASK) != EXPONENT_MASK;
}


/** \brief Check if number is zero.
 */
bool isZero(const double number)
{
    BitwiseDouble u = {number};
    return (u.u64 & (EXPONENT_MASK | SIGNIFICAND_MASK)) == 0;
}


/** \brief Check if number is positive.
 */
bool isPositive(const double number)
{
    BitwiseDouble u = {number};
    return (u.u64 & SIGN_MASK) == 0;
}

}   /* detail */
}   /* lexi */
