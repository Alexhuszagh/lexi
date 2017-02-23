//  :copyright: (c) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexi macro definitions.
 */

#pragma once

#include <stdexcept>

// MACROS -- GENERALIZED
// ---------------------


#define LEXI_ID(x) x
#define LEXI_STRINGIFY(x) #x
#define LEXI_ASSERT(x, y)                                               \
    if (!(x)) {                                                         \
        throw std::runtime_error(LEXI_STRINGIFY(y));                    \
    }


// MACROS -- CONFIGURATION
// -----------------------

// Use JS-like notation by default

#ifndef LEXI_NULL
#   define LEXI_NULL LEXI_STRINGIFY(null)
#endif      // LEXI_NULL

#ifndef LEXI_TRUE
#   define LEXI_TRUE LEXI_STRINGIFY(true)
#endif      // LEXI_TRUE

#ifndef LEXI_FALSE
#   define LEXI_FALSE LEXI_STRINGIFY(false)
#endif      // LEXI_FALSE

#ifndef LEXI_NAN
#   define LEXI_NAN LEXI_STRINGIFY(NaN)
#endif      // LEXI_NAN

#ifndef LEXI_INFINITY
#   define LEXI_INFINITY LEXI_STRINGIFY(Infinity)
#endif      // LEXI_INFINITY


#ifndef LEXI_NEGATIVE_INFINITY
#   define LEXI_NEGATIVE_INFINITY LEXI_STRINGIFY(-Infinity)
#endif      // LEXI_NEGATIVE_INFINITY
