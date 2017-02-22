//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Integer conversion to strings.
 */

#pragma once

#include "diyfp.hpp"


namespace lexi
{
namespace detail
{
// FUNCTIONS
// ---------

/** \brief Convert unsigned 32-bit value to string
 */
char * u32toa(uint32_t value,
    char *buffer);

/** \brief Convert signed 32-bit value to string
 */
char * i32toa(int32_t value,
    char *buffer);

/** \brief Convert unsigned 64-bit value to string
 */
char * u64toa(uint64_t value,
    char *buffer);

/** \brief Convert signed 64-bit value to string
 */
char * i64toa(int64_t value,
    char *buffer);

}   /* detail */
}   /* lexi */
