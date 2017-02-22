//  :copyright: (c) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexi macro definitions.
 */

#pragma once

#include <stdexcept>


#define LEXI_ID(x) x
#define LEXI_STRINGIFY(x) #x
#define LEXI_ASSERT(x) std::runtime_error(LEXI_STRINGIFY(x))
