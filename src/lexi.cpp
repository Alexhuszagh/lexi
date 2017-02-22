//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Overload for .
 */

#include "lexi/lexi.hpp"


namespace lexi
{
// FUNCTIONS
// ---------


/** \brief Overload returning reference for existing string types.
 */
const std::string & lexi(const std::string &string)
{
    return string;
}

}   /* lexi */
