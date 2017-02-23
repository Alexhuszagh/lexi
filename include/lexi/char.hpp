//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for character types.
 */

#pragma once

#include <string>


namespace lexi
{
// OBJECTS
// -------


/** \brief Generic character formatter.
 */
class FormatChar
{
protected:
    char buffer_[2];

public:
    FormatChar(const char c);
    FormatChar(const unsigned char c);

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


/** \brief Generic character extractor.
 */
class ExtractChar
{
protected:
    char c;

public:
    ExtractChar(const std::string &string);

    // CONVERSIONS
    explicit operator char() const;
    explicit operator unsigned char() const;
};


}   /* lexi */
