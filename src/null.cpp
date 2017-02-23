//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for null types.
 */

#include "lexi/null.hpp"
#include "lexi/detail/define.hpp"

#include <cstring>


namespace lexi
{
// CONSTANTS
// ---------

static const char NULL_STRING[] = LEXI_NULL;

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
    return 4;
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
std::string FormatNull::string() const
{
    return std::string(data(), size());
}


/** \brief Escape characters and get string.
 */
std::string FormatNull::escape() const
{
    return string();
}


/** \brief Convert input to JSON-literal.
 */
std::string FormatNull::jsonify() const
{
    return string();
}


/** \brief Conversion to std::string.
 */
FormatNull::operator std::string() const
{
    return string();
}


ExtractNull::ExtractNull(const std::string &string)
{
    LEXI_ASSERT(string == NULL_STRING, "String is not null.");
}


/** \brief Conversion to nullptr.
 */
ExtractNull::operator std::nullptr_t() const
{
    return nullptr;
}

}   /* lexi */
