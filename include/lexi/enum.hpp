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


/** \brief Generic enum extractor.
 */
struct ExtractEnum: protected ExtractInt
{
    using ExtractInt::ExtractInt;

    template <typename Enum>
    explicit operator Enum() const;
};


// IMPLEMENTATION
// --------------


template <typename Enum>
FormatEnum::FormatEnum(const Enum value):
    FormatInt(static_cast<underlying_type_t<Enum>>(value))
{}


/** \brief Convert to enum.
 */
template <typename Enum>
ExtractEnum::operator Enum() const
{
    return static_cast<Enum>(static_cast<underlying_type_t<Enum>>(data_));
}

}   /* lexi */
