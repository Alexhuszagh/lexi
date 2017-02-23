//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup JSON
 *  \brief Type detection.
 */

#pragma once

#include <ios>
#include <limits>
#include <type_traits>


namespace lexi
{
namespace detail
{
// SFINAE
// ------

template <typename T>
struct is_null_pointer: std::is_same<typename std::remove_cv<T>::type, std::nullptr_t>
{};

template <typename T>
struct is_bool: std::is_same<typename std::remove_cv<T>::type, bool>
{};

template <typename T>
struct is_char: std::is_same<typename std::remove_cv<T>::type, char>
{};

template <typename T>
struct is_unsigned_char: std::is_same<typename std::remove_cv<T>::type, unsigned char>
{};

template <typename T>
struct is_integer: std::false_type
{};

template <>
struct is_integer<short>: std::true_type
{};

template <>
struct is_integer<unsigned short>: std::true_type
{};

template <>
struct is_integer<int>: std::true_type
{};

template <>
struct is_integer<unsigned int>: std::true_type
{};

template <>
struct is_integer<long>: std::true_type
{};

template <>
struct is_integer<unsigned long>: std::true_type
{};

template <>
struct is_integer<long long>: std::true_type
{};

template <>
struct is_integer<unsigned long long>: std::true_type
{};

template <typename T>
struct is_float: std::false_type
{};

template <>
struct is_float<float>: std::true_type
{};

template <>
struct is_float<double>: std::true_type
{};

template <>
struct is_float<long double>: std::true_type
{};

template <typename T>
struct is_std_string: std::is_base_of<std::string, T>
{};

template <typename T>
struct is_string_literal: std::is_same<char*, typename std::remove_cv<typename std::decay<T>::type>::type>
{};

template <typename T>
struct is_cstr: std::is_same<const char*, typename std::remove_cv<typename std::decay<T>::type>::type>
{};

template <typename T>
struct is_fpos: std::false_type
{};

template <typename T>
struct is_fpos<std::fpos<T>>: std::true_type
{};

}   /* detail */

// TYPES
// -----

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template <typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

template <typename T>
using underlying_type_t = typename std::underlying_type<T>::type;

template <typename T>
using remove_cv_t = typename std::remove_cv<T>::type;

template <typename T>
constexpr bool is_null_pointer_v = detail::is_null_pointer<T>::value;

template <typename T>
constexpr bool is_enum_v = std::is_enum<T>::value;

template <typename T>
constexpr bool is_bool_v = detail::is_bool<T>::value;

template <typename T>
constexpr bool is_char_v = detail::is_char<T>::value;

template <typename T>
constexpr bool is_unsigned_char_v = detail::is_unsigned_char<T>::value;

template <typename T>
constexpr bool is_character_v = is_char_v<T> || is_unsigned_char_v<T>;

template <typename T>
constexpr bool is_integer_v = detail::is_integer<T>::value;

template <typename T>
constexpr bool is_float_v = detail::is_float<T>::value;

template <typename T>
constexpr bool is_std_string_v = detail::is_std_string<T>::value;

template <typename T>
constexpr bool is_string_literal_v = detail::is_string_literal<T>::value;

template <typename T>
constexpr bool is_cstr_v = detail::is_cstr<T>::value;

template <typename T>
constexpr bool is_string_v = is_std_string_v<T> || is_cstr_v<T> || is_string_literal_v<T>;

template <typename T>
constexpr bool is_fpos_v = detail::is_fpos<T>::value;

}   /* lexi */
