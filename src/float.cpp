//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for floating-point types.
 */

#include "lexi/float.hpp"
#include "lexi/detail/define.hpp"
#include "lexi/detail/dtoa.hpp"
#include "lexi/detail/ieee754.hpp"

#include <cstring>


namespace lexi
{
// CONSTANTS
// ---------

static const char NAN_STRING[] = LEXI_NAN;
static const char INFINITY_STRING[] = LEXI_INFINITY;
static const char NEGATIVE_INFINITY_STRING[] = LEXI_NEGATIVE_INFINITY;

// OBJECTS
// -------


/** \brief Format floating point number into buffer.
 */
void FormatFloat::format(long double value)
{
    first = buffer_;
    last = buffer_;
    if (!detail::isFinite(value)) {
        // IEEE754 special numbers, use custom strings.
        if (detail::isNan(value)) {
            strncpy(first, NAN_STRING, sizeof(NAN_STRING));
            last += sizeof(NAN_STRING) - 1;
        } else if (detail::isInfinity(value)) {
            strncpy(first, INFINITY_STRING, sizeof(INFINITY_STRING));
            last += sizeof(INFINITY_STRING) - 1;
        } else {
            strncpy(first, NEGATIVE_INFINITY_STRING, sizeof(NEGATIVE_INFINITY_STRING));
            last += sizeof(NEGATIVE_INFINITY_STRING) - 1;
        }
    } else {
        last = detail::dtoa(value, buffer_);
    }
}


FormatFloat::FormatFloat(float value)
{
    format(value);
}


FormatFloat::FormatFloat(double value)
{
    format(value);
}


FormatFloat::FormatFloat(long double value)
{
    format(value);
}


/** \brief Size of current buffer.
 */
size_t FormatFloat::size() const
{
    return last - first;
}


/** \brief Alias for `size()`.
 */
size_t FormatFloat::length() const
{
    return size();
}


/** \brief Return pointer to buffer content.
 *
 *  Compliant with C++11's `data()`, which adds a null-terminator.
 */
const char * FormatFloat::data() const
{
    return c_str();
}


/** \brief Return null-terminated buffer.
 */
const char * FormatFloat::c_str() const
{
    return first;
}


/** \brief Conversion to std::string.
 */
FormatFloat::operator std::string() const
{
    return std::string(data(), size());
}


ExtractFloat::ExtractFloat(const std::string &string)
{
    // TODO: optimize this.
    data_ = std::strtold(string.data(), nullptr);
}


/** \brief Conversion to float.
 */
ExtractFloat::operator float() const
{
    return data_;
}


/** \brief Conversion to double.
 */
ExtractFloat::operator double() const
{
    return data_;
}


/** \brief Conversion to long double.
 */
ExtractFloat::operator long double() const
{
    return data_;
}

}   /* lexi */
