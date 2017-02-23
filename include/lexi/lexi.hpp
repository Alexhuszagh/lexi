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


/** \brief Type detection for formatting overloads.
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

    template <typename T>
    enable_if_t<is_enum_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatEnum(t));
    }

    template <typename T>
    enable_if_t<is_fpos_v<T>, std::string>
    operator()(const T t)
    {
        return std::string(FormatInt(std::streamoff(t)));
    }
};


/** \brief Type detection for extraction overloads.
 */
template <typename T>
struct Extract
{
    template <typename U = T>
    enable_if_t<is_null_pointer_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractNull(string));
    }

    template <typename U = T>
    enable_if_t<is_bool_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractBool(string));
    }

    template <typename U = T>
    enable_if_t<is_character_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractChar(string));
    }

    template <typename U = T>
    enable_if_t<is_integer_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractInt(string));
    }


    template <typename U = T>
    enable_if_t<is_float_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractFloat(string));
    }

    template <typename U = T>
    enable_if_t<is_enum_v<U>, T>
    operator()(const std::string &string)
    {
        return T(ExtractEnum(string));
    }

    template <typename U = T>
    enable_if_t<is_fpos_v<U>, T>
    operator()(const std::string &string)
    {
        return T(std::streamoff(ExtractInt(string)));
    }
};


// FUNCTIONS
// ---------


/** \brief Extract value from string.
 */
template <
    typename T,
    typename = enable_if_t<!is_string_v<T>, T>
>
T lexi(const std::string &string)
{
    return Extract<T>()(string);
}


/** \brief Extract value from string literal.
 */
template <
    typename T,
    typename = enable_if_t<!is_string_v<T>, T>
>
T lexi(const char *string)
{
    return Extract<T>()(string);
}


/** \brief Format value from string.
 */
template <
    typename T,
    enable_if_t<!is_string_v<T>, T>* = nullptr
>
std::string lexi(const T &t)
{
    return Format()(t);
}


/** \brief Overload returning reference for existing string types.
 */
template <
    typename T,
    enable_if_t<is_string_v<T>, T>* = nullptr
>
std::string lexi(const T &t)
{
    return t;
}

}   /* lexi */
