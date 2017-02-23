//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test null formatting and extraction.
 */

#include <lexi/char.hpp>
#include <gtest/gtest.h>


// TESTS
// -----


TEST(FormatChar, Format)
{
    auto TEST_STRING  = [](const char c, const std::string &expected) {
        EXPECT_EQ(lexi::FormatChar(c).string(), expected);
    };
    auto TEST_ESCAPE  = [](const char c, const std::string &expected) {
        EXPECT_EQ(lexi::FormatChar(c).escape(), expected);
    };
    auto TEST_JSONIFY  = [](const char c, const std::string &expected) {
        EXPECT_EQ(lexi::FormatChar(c).jsonify(), expected);
    };

    TEST_STRING('\0', std::string("\0", 1));
    TEST_STRING('\b', "\b");
    TEST_STRING('\f', "\f");
    TEST_STRING('a', "a");

    TEST_ESCAPE('\0', std::string("\\\0", 2));
    TEST_ESCAPE('\b', "\\\b");
    TEST_ESCAPE('\f', "\\\f");
    TEST_ESCAPE('a', "a");

    TEST_JSONIFY('\0', "\"\\u0000\"");
    TEST_JSONIFY('\b', "\"\\b\"");
    TEST_JSONIFY('\f', "\"\\f\"");
    TEST_JSONIFY('a', "\"a\"");
}

