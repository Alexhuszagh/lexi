//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for boolean types.
 */

#include "lexi/bool.hpp"
#include "lexi/detail/define.hpp"

#include <cstring>


namespace lexi
{
// CONSTANTS
// ---------

static const char TRUE_STRING[] = LEXI_TRUE;
static const char FALSE_STRING[] = LEXI_FALSE;

// OBJECTS
// -------


FormatBool::FormatBool(const bool b)
{
    if (b) {
        strncpy(buffer_, TRUE_STRING, sizeof(TRUE_STRING));
        size_ = 4;
    } else {
        strncpy(buffer_, FALSE_STRING, sizeof(FALSE_STRING));
        size_ = 5;
    }
}


/** \brief Size of current buffer.
 */
size_t FormatBool::size() const
{
    return size_;
}


/** \brief Alias for `size()`.
 */
size_t FormatBool::length() const
{
    return size();
}


/** \brief Return pointer to buffer content.
 *
 *  Compliant with C++11's `data()`, which adds a null-terminator.
 */
const char * FormatBool::data() const
{
    return c_str();
}


/** \brief Return null-terminated buffer.
 */
const char * FormatBool::c_str() const
{
    return buffer_;
}


/** \brief Conversion to std::string.
 */
FormatBool::operator std::string() const
{
    return std::string(data(), size());
}


ExtractBool::ExtractBool(const std::string &string)
{
    if (string == TRUE_STRING) {
        data_ = true;
    } else if (string == FALSE_STRING) {
        data_ = false;
    } else {
        throw std::runtime_error("String is not boolean.");
    }
}


/** \brief Conversion to boolean.
 */
ExtractBool::operator bool() const
{
    return data_;
}

}   /* lexi */
