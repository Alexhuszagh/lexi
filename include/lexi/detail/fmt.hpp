//  :copyright: (c) 2012-2016 Victor Zverovich.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for integer types.
 */

#pragma once

#include <limits>
#include <string>


namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

constexpr int INTEGER_SIZE = std::numeric_limits<unsigned long long>::digits10 + 3;
constexpr char DIGITS[] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";

}   /* detail */
}   /* lexi */
