//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for null types.
 */

#include "lexi/null.hpp"

#include <cstring>


namespace lexi
{
// CONSTANTS
// ---------

// Use JS-like notation by default
static const char NULL_STRING[5] = "null";

// OBJECTS
// -------


FormatNull::FormatNull()
{
    strncpy(buffer_, NULL_STRING, sizeof(NULL_STRING));
}


FormatNull::FormatNull(const std::nullptr_t nullp)
{
    strncpy(buffer_, NULL_STRING, sizeof(NULL_STRING));
}


/** \brief Size of current buffer.
 */
size_t FormatNull::size() const
{
    return 5;
}


/** \brief Alias for `size()`.
 */
size_t FormatNull::length() const
{
    return size();
}


/** \brief Return pointer to buffer content.
 *
 *  Compliant with C++11's `data()`, which adds a null-terminator.
 */
const char * FormatNull::data() const
{
    return c_str();
}


/** \brief Return null-terminated buffer.
 */
const char * FormatNull::c_str() const
{
    return buffer_;
}


/** \brief Conversion to std::string.
 */
FormatNull::operator std::string() const
{
    return std::string(data(), size());
}


}   /* lexi */
