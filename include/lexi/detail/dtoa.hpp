//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Double conversion to strings.
 */

#pragma once

#include "diyfp.hpp"


namespace lexi
{
namespace detail
{
// FUNCTIONS
// ---------

/** \brief Format finite double to string buffer.
 */
char * dtoa(double value,
    char *buffer);

}   /* detail */
}   /* lexi */
