//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for integer types.
 */

#pragma once

#include "detail/fmt.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Fast integer formatter.
 */
class FormatInt
{
protected:
    char buffer_[detail::INTEGER_SIZE];
    char *first;
    char *last;

public:
    FormatInt(int8_t value);
    FormatInt(uint8_t value);
    FormatInt(short value);
    FormatInt(unsigned short value);
    FormatInt(int value);
    FormatInt(unsigned int value);
    FormatInt(long value);
    FormatInt(unsigned long value);
    FormatInt(long long value);
    FormatInt(unsigned long long value);

    // DATA
    size_t size() const;
    size_t length() const;
    const char * data() const;
    const char * c_str() const;

    // CONVERSIONS
    explicit operator std::string() const;
};


/** \brief Fast integer lexical reader.
 */
class ExtractInt
{
protected:
    unsigned long long data_;

public:
    ExtractInt(const std::string &string);

    // CONVERSIONS
    explicit operator int8_t() const;
    explicit operator uint8_t() const;
    explicit operator short() const;
    explicit operator unsigned short() const;
    explicit operator int() const;
    explicit operator unsigned int() const;
    explicit operator long() const;
    explicit operator unsigned long() const;
    explicit operator long long() const;
    explicit operator unsigned long long() const;
};

}   /* lexi */
