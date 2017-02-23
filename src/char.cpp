//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for character types.
 */

#include "lexi/char.hpp"
#include "lexi/detail/define.hpp"
#include "lexi/detail/string.hpp"


namespace lexi
{
// OBJECTS
// -------


FormatChar::FormatChar(const char c)
{
    buffer_[0] = c;
    buffer_[1] = '\0';
}


FormatChar::FormatChar(const unsigned char c)
{
    buffer_[0] = static_cast<const char>(c);
    buffer_[1] = '\0';
}


/** \brief Size of current buffer.
 */
size_t FormatChar::size() const
{
    return 1;
}


/** \brief Alias for `size()`.
 */
size_t FormatChar::length() const
{
    return size();
}


/** \brief Return pointer to buffer content.
 *
 *  Compliant with C++11's `data()`, which adds a null-terminator.
 */
const char * FormatChar::data() const
{
    return c_str();
}


/** \brief Return null-terminated buffer.
 */
const char * FormatChar::c_str() const
{
    return buffer_;
}


/** \brief Conversion to std::string.
 */
std::string FormatChar::string() const
{
    return std::string(data(), size());
}


/** \brief Escape characters and get string.
 */
std::string FormatChar::escape() const
{
    return detail::escape(string());
}


/** \brief Convert input to JSON-literal.
 */
std::string FormatChar::jsonify() const
{
    return "\"" + detail::jsonify(string()) + "\"";
}


/** \brief Conversion to std::string.
 */
FormatChar::operator std::string() const
{
    return string();
}


ExtractChar::ExtractChar(const std::string &string)
{
    LEXI_ASSERT(!string.empty(), "Cannot extract character from empty string.");
    c = string.front();
}


/** \brief Conversion to char.
 */
ExtractChar::operator char() const
{
    return c;
}


/** \brief Conversion to char.
 */
ExtractChar::operator unsigned char() const
{
    return static_cast<unsigned char>(c);
}

}   /* lexi */
