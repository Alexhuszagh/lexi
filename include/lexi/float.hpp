//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for floating-point types.
 */

#pragma once

#include "detail/fmt.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Fast floating-point number formatter.
 */
class FormatFloat
{
protected:
    char buffer_[detail::FLOAT_SIZE];
    char *first;
    char *last;

    void format(long double value);

public:
    FormatFloat(float value);
    FormatFloat(double value);
    FormatFloat(long double value);

    // DATA
    size_t size() const;
    size_t length() const;
    const char * data() const;
    const char * c_str() const;

    std::string string() const;
    std::string escape() const;
    std::string jsonify() const;

    // CONVERSIONS
    explicit operator std::string() const;
};


/** \brief Fast floating-point number lexical reader.
 */
class ExtractFloat
{
protected:
    long double data_;

public:
    ExtractFloat(const std::string &string);

    // CONVERSIONS
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;
};

}   /* lexi */
