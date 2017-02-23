//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test null formatting and extraction.
 */

#include <lexi/null.hpp>
#include <gtest/gtest.h>


// TESTS
// -----


TEST(FormatNull, Format)
{
    auto TEST_STRING  = [](std::nullptr_t nullp, const std::string &expected) {
        EXPECT_EQ(lexi::FormatNull(nullp).string(), expected);
    };
    auto TEST_ESCAPED  = [](std::nullptr_t nullp, const std::string &expected) {
        EXPECT_EQ(lexi::FormatNull(nullp).string(), expected);
    };
    auto TEST_JSONIFY  = [](std::nullptr_t nullp, const std::string &expected) {
        EXPECT_EQ(lexi::FormatNull(nullp).jsonify(), expected);
    };

    TEST_STRING(0, "null");
    TEST_ESCAPED(0, "null");
    TEST_JSONIFY(0, "null");
    TEST_STRING(NULL, "null");
    TEST_STRING(nullptr, "null");
    TEST_STRING(std::nullptr_t(), "null");
}
