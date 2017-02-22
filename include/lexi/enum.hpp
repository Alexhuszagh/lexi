//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for custom enumerated types.
 */

#pragma once

#include "int.hpp"
#include "detail/type.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Generic enum formatter.
 */
struct FormatEnum: FormatInt
{
    template <typename Enum>
    FormatEnum(const Enum value);
};


// IMPLEMENTATION
// --------------


template <typename Enum>
FormatEnum::FormatEnum(const Enum value):
    FormatInt(static_cast<underlying_type_t<Enum>>(value))
{}


}   /* lexi */
