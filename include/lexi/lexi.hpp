//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexi public header.
 */

#pragma once

#include "bool.hpp"
#include "char.hpp"
#include "int.hpp"
#include "enum.hpp"
#include "float.hpp"
#include "null.hpp"
#include "detail/type.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Type detection and formatting overloads.
 */
struct Format
{
    template <typename T>
    enable_if_t<is_null_pointer_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatNull(t));
    }

    template <typename T>
    enable_if_t<is_enum_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatEnum(t));
    }

    template <typename T>
    enable_if_t<is_bool_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatBool(t));
    }

    template <typename T>
    enable_if_t<is_character_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatChar(t));
    }

    template <typename T>
    enable_if_t<is_integer_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatInt(t));
    }

    template <typename T>
    enable_if_t<is_float_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatFloat(t));
    }

    // TODO: need to check if string...
};


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
    typename = enable_if_t<!is_same_v<T, std::string>, T>
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
    typename = enable_if_t<!is_same_v<T, std::string>, T>
>
std::string lexi(const T &t)
{
    return Format()(t);
}

//
///** \brief Overload returning reference for existing string types.
// */
//const std::string & lexi(const std::string &string);

}   /* lexi */
