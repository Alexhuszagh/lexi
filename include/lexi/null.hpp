//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Lexical formatting for null types.
 */

#pragma once

#include "detail/fmt.hpp"


namespace lexi
{
// OBJECTS
// -------


/** \brief Generic null formatter.
 */
class FormatNull
{
protected:
    char buffer_[5];

public:
    FormatNull();
    FormatNull(const std::nullptr_t nullp);

    // DATA
    size_t size() const;
    size_t length() const;
    const char * data() const;
    const char * c_str() const;

    // CONVERSIONS
    explicit operator std::string() const;
};


}   /* lexi */
