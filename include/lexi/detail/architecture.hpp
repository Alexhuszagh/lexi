// :copyright: (c) 2012 Petroules Corporation. All rights reserved.
// :copyright: (c) 2015-2017 The Regents of the University of California.
// :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Architecture detection.
 *
 *  Detect sytsem architecture via preprocessor definitions.
 */

#pragma once


// WINDOWS
// -------

#if _WIN32 || _WIN64
#   if _WIN64
#       define SYSTEM_ARCHITECTURE 64
#   elif _WIN32
#       define SYSTEM_ARCHITECTURE 32
#   elif _WIN16
#       define SYSTEM_ARCHITECTURE 16
#   endif
#endif

// GCC
// ---

#if __GNUC__
#   if __x86_64__ || __ppc64__ || __amd64__ || __LP64__ || _M_X64 || __ia64 || _M_IA64 || __aarch64__ || __powerpc64__
#       define SYSTEM_ARCHITECTURE 64
#   else
#       define SYSTEM_ARCHITECTURE 32
#   endif
#endif
