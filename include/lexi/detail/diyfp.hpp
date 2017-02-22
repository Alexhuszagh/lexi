//  :copyright: (c) 2014 Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Double conversion to strings.
 */

#pragma once

#include <cstdint>


namespace lexi
{
namespace detail
{
// OBJECTS
// -------


struct DiyFp
{
    uint64_t f;
    int e;

    DiyFp();
    DiyFp(uint64_t f, int e);
    DiyFp(double d);

    DiyFp operator-(const DiyFp &other) const;
    DiyFp operator*(const DiyFp &other) const;
    DiyFp normalize() const;
    DiyFp normalizeBoundary() const;
    void normalizedBoundaries(DiyFp *minus, DiyFp *plus) const;
};

}   /* detail */
}   /* lexi */
