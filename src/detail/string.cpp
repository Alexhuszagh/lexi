//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief String utilities.
 */

#include "lexi/detail/string.hpp"


namespace lexi
{
namespace detail
{
// CONSTANTS
// ---------

static constexpr char HEX[] = "0123456789abcdef";

// FUNCTIONS
// ---------


/** \brief Escape printable, non-Unicode, non-alphanumeric characters.
 *
 *  Escapes all ASCII non-alphanumeric characters, assuming
 *  UTF-8 source encoding.
 */
std::string escape(const std::string &src)
{
    std::string dst;
    dst.reserve(src.size() * 2 + 1);

    for (const char c: src) {
        if ((c >= 0 && c <= 47) ||      // Null - /
            (c >= 58 && c <= 64) ||     // : - @
            (c >= 91 && c <= 96) ||     // [ - `]
            (c >= 123 && c <= 126)) {   // ( - ~
            dst.push_back('\\');
        }
        dst.push_back(c);
    }

    dst.shrink_to_fit();
    return dst;
}


/** \brief Convert characters to JSON-literal forms.
 *
 *  Convert all escape sequences to '\\' and the letter.
 */
std::string jsonify(const std::string &src)
{
    std::string dst;
    dst.reserve(src.size() * 2 + 1);
    for (const char c: src) {
        switch (c) {
            //case '\0':
            case '\b':
                dst.push_back('\\');
                dst.push_back('b');
                break;
            case '\f':
                dst.push_back('\\');
                dst.push_back('f');
                break;
            case '\n':
                dst.push_back('\\');
                dst.push_back('n');
                break;
            case '\r':
                dst.push_back('\\');
                dst.push_back('r');
                break;
            case '\t':
                dst.push_back('\\');
                dst.push_back('t');
                break;
            case '\\':
                dst.push_back('\\');
                dst.push_back('\\');
                break;
            case '"':
                dst.push_back('\\');
                dst.push_back('"');
                break;
            default:
                if (c >= 0x00 && c <= 0x1f) {
                    dst += "\\u00";
                    dst.push_back(HEX[c >> 4]);
                    dst.push_back(HEX[c & 0x0f]);
                } else {
                    dst.push_back(c);
                }
        }
    }

    dst.shrink_to_fit();
    return dst;
}

}   /* detail */
}   /* lexi */
