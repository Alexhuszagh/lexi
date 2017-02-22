//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Floating point number specifications.
 */

#pragma once

#include <cstdint>

namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

constexpr uint64_t EXPONENT_MASK = 0x7FF0000000000000ULL;
constexpr uint64_t SIGNIFICAND_MASK = 0x000FFFFFFFFFFFFFULL;
constexpr uint64_t SIGN_MASK = 0x8000000000000000ULL;

// OBJECTS
// -------

union BitwiseDouble
{
    double d;
    uint64_t u64;
};

// FUNCTIONS
// ---------

/** \brief Check if number is NaN.
 */
bool isNan(const double number);

/** \brief Check if number is inf.
 */
bool isInf(const double number);

/** \brief Check if number is -inf.
 */
bool isNegativeInfinity(const double number);

/** \brief Check if number is inf.
 */
bool isInfinity(const double number);

/** \brief Check if number is not NaN or inf.
 */
bool isFinite(const double number);

/** \brief Check if number is zero.
 */
bool isZero(const double number);

/** \brief Check if number is positive.
 */
bool isPositive(const double number);

}   /* detail */
}   /* lexi */
