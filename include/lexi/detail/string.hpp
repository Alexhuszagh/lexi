//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief String utilities.
 */

#pragma once

#include <string>


namespace lexi
{
namespace detail
{
// FUNCTIONS
// ---------

/** \brief Escape printable, non-Unicode, non-alphanumeric characters.
 */
std::string escape(const std::string &src);

/** \brief Convert characters to JSON-literal forms.
 */
std::string jsonify(const std::string &src);

}   /* detail */
}   /* lexi */
