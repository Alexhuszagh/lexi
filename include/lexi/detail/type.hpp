//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup JSON
 *  \brief Type detection.
 */

#pragma once

#include <type_traits>


namespace lexi
{
namespace detail
{
// TYPES
// -----

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template <typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

template< class T >
using underlying_type_t = typename std::underlying_type<T>::type;

}   /* detail */
}   /* lexi */
