//  :copyright: (c) 2012-2016 Victor Zverovich.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for integer types.
 */

#include "lexi/int.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Format unsigned value in reverse amd return number of digits.
 *
 *  Uses integer division for a group of two digits instead of for every
 *  digit, since it is slow. The idea comes from the talk by Alexandrescu
 *  "Three Optimization Tips for C++".
 */
char * FormatInt::unsigned_(unsigned long long value)
{
    char *end = buffer_ + detail::INTEGER_SIZE - 1;
    while (value >= 100) {
        auto index = static_cast<unsigned int>((value % 100) * 2);
        value /= 100;
        *--end = detail::DIGITS[index + 1];
        *--end = detail::DIGITS[index];
    }
    if (value < 10) {
        *--end = static_cast<char>('0' + value);
        return end;
    }
    unsigned int index = static_cast<unsigned int>(value * 2);
    *--end = detail::DIGITS[index + 1];
    *--end = detail::DIGITS[index];

    return end;
}


/** \brief Format signed value in reverse amd return number of digits.
 */
char * FormatInt::signed_(long long value)
{
    bool negative = value < 0;
    unsigned long long number = negative ? -value : value;
    data_ = unsigned_(number);
    if (negative) {
        *--data_ = '-';
    }

    return data_;
}


/** \brief Add null trailing character.
 */
void FormatInt::terminate()
{
    buffer_[detail::INTEGER_SIZE - 1] = '\0';
}


FormatInt::FormatInt(short value)
{
    signed_(value);
    terminate();
}


FormatInt::FormatInt(unsigned short value):
    data_(unsigned_(value))
{
    terminate();
}


FormatInt::FormatInt(int value)
{
    signed_(value);
    terminate();
}


FormatInt::FormatInt(unsigned int value):
    data_(unsigned_(value))
{
    terminate();
}


FormatInt::FormatInt(long value)
{
    signed_(value);
    terminate();
}


FormatInt::FormatInt(unsigned long value):
    data_(unsigned_(value))
{
    terminate();
}


FormatInt::FormatInt(long long value)
{
    signed_(value);
    terminate();
}


FormatInt::FormatInt(unsigned long long value):
    data_(unsigned_(value))
{
    terminate();
}


/** \brief Number of characters written to the output buffer.
 */
size_t FormatInt::size() const
{
    return buffer_ - data_ + detail::INTEGER_SIZE - 1;
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
    return data_;
}


/** \brief Conversion to std::string.
 */
FormatInt::operator std::string() const
{
    return std::string(data(), size());
}

}   /* lexi */
