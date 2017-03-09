//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for integer types.
 */

#include "lexi/int.hpp"
#include "lexi/detail/architecture.hpp"
#include "lexi/detail/itoa.hpp"


namespace lexi
{
// OBJECTS
// -------


FormatInt::FormatInt(int8_t value)
{
    first = buffer_;
    last = detail::i32toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(uint8_t value)
{
    first = buffer_;
    last = detail::u32toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(short value)
{
    first = buffer_;
    last = detail::i32toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(unsigned short value)
{
    first = buffer_;
    last = detail::u32toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(int value)
{
    first = buffer_;
    last = detail::i32toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(unsigned int value)
{
    first = buffer_;
    last = detail::u32toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(long value)
{
    first = buffer_;

    #if !defined(_WIN32) && SYSTEM_ARCHITECTURE == 64
        // longs are 64-bits on all 64-bit systems except Windows
        last = detail::i64toa(value, buffer_);
    #else
        last = detail::i32toa(value, buffer_);
    #endif

    *last = '\0';
}


FormatInt::FormatInt(unsigned long value)
{
    first = buffer_;

    #if !defined(_WIN32) && SYSTEM_ARCHITECTURE == 64
        // longs are 64-bits on all 64-bit systems except Windows
        last = detail::u64toa(value, buffer_);
    #else
        last = detail::u32toa(value, buffer_);
    #endif

    *last = '\0';
}


FormatInt::FormatInt(long long value)
{
    first = buffer_;
    last = detail::i64toa(value, buffer_);
    *last = '\0';
}


FormatInt::FormatInt(unsigned long long value)
{
    first = buffer_;
    last = detail::u64toa(value, buffer_);
    *last = '\0';
}


/** \brief Number of characters written to the output buffer.
 */
size_t FormatInt::size() const
{
    return last - first;
}


/** \brief Alias for `size()`.
 */
size_t FormatInt::length() const
{
    return size();
}


/** \brief Return pointer to buffer content.
 *
 *  Compliant with C++11's `data()`, which adds a null-terminator.
 */
const char * FormatInt::data() const
{
    return c_str();
}


/** \brief Return null-terminated buffer.
 */
const char * FormatInt::c_str() const
{
    return first;
}


/** \brief Conversion to std::string.
 */
std::string FormatInt::string() const
{
    return std::string(data(), size());
}


/** \brief Escape characters and get string.
 */
std::string FormatInt::escape() const
{
    return string();
}


/** \brief Convert input to JSON-literal.
 */
std::string FormatInt::jsonify() const
{
    return string();
}


/** \brief Conversion to std::string.
 */
FormatInt::operator std::string() const
{
    return string();
}


ExtractInt::ExtractInt(const std::string &string)
{
    // TODO: optimize this.
    data_ = std::strtoull(string.data(), nullptr, 10);
}


/** \brief Conversion to int8_t.
 */
ExtractInt::operator int8_t() const
{
    return static_cast<long long>(data_);
}


/** \brief Conversion to uint8_t.
 */
ExtractInt::operator uint8_t() const
{
    return data_;
}


/** \brief Conversion to short.
 */
ExtractInt::operator short() const
{
    return static_cast<long long>(data_);
}


/** \brief Conversion to unsigned short.
 */
ExtractInt::operator unsigned short() const
{
    return data_;
}


/** \brief Conversion to int.
 */
ExtractInt::operator int() const
{
    return static_cast<long long>(data_);
}


/** \brief Conversion to unsigned int.
 */
ExtractInt::operator unsigned int() const
{
    return data_;
}


/** \brief Conversion to long.
 */
ExtractInt::operator long() const
{
    return static_cast<long long>(data_);
}


/** \brief Conversion to unsigned long.
 */
ExtractInt::operator unsigned long() const
{
    return data_;
}


/** \brief Conversion to long long.
 */
ExtractInt::operator long long() const
{
    return static_cast<long long>(data_);
}


/** \brief Conversion to unsigned long long.
 */
ExtractInt::operator unsigned long long() const
{
    return data_;
}

}   /* lexi */
