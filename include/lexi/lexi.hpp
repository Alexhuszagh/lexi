//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexi public header.
 */

#pragma once

#include "int.hpp"
#include "detail/type.hpp"


namespace lexi
{
// OBJECTS
// -------


// TODO: sfinae for type detection for formatting
template <typename T>
struct Format
{};


// TODO: sfinae for type detection for extraction
template <typename T>
struct Extract
{};


// FUNCTIONS
// ---------


/** \brief Extract value from string.
 */
template <
    typename T,
    typename = detail::enable_if_t<!detail::is_same_v<T, std::string>, T>
>
T lexi(const std::string &string)
{
    // TODO: implement
    return T();
}


/** \brief Format value from string.
 */
template <
    typename T,
    typename = detail::enable_if_t<!detail::is_same_v<T, std::string>, T>
>
std::string lexi(const T &t)
{
    // TODO: implement
    return std::string();
}


/** \brief Overload returning reference for existing string types.
 */
const std::string & lexi(const std::string &string);

}   /* lexi */
