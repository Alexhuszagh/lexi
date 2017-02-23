//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for boolean types.
 */

#pragma once

#include <string>


namespace lexi
{
// OBJECTS
// -------


/** \brief Generic boolean formatter.
 */
class FormatBool
{
protected:
    char buffer_[6];
    size_t size_;

public:
    FormatBool(const bool b);

    // DATA
    size_t size() const;
    size_t length() const;
    const char * data() const;
    const char * c_str() const;

    // CONVERSIONS
    explicit operator std::string() const;
};


/** \brief Generic boolean extractor.
 */
class ExtractBool
{
protected:
    bool data_;

public:
    ExtractBool(const std::string &string);

    // CONVERSIONS
    explicit operator bool() const;
};

}   /* lexi */
