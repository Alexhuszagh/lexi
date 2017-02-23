//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test boolean formatting and extraction.
 */

#include <lexi/bool.hpp>
#include <gtest/gtest.h>


// TESTS
// -----


TEST(FormatBool, Format)
{
    auto TEST_BOOL  = [](bool b, const std::string &expected) {
        EXPECT_EQ(lexi::FormatBool(b).string(), expected);
    };
    auto TEST_CONST_BOOL  = [](const bool b, const std::string &expected) {
        EXPECT_EQ(lexi::FormatBool(b).string(), expected);
    };
    auto TEST_VOLATILE_BOOL  = [](volatile bool b, const std::string &expected) {
        EXPECT_EQ(lexi::FormatBool(b).string(), expected);
    };
    auto TEST_CV_BOOL  = [](volatile bool b, const std::string &expected) {
        EXPECT_EQ(lexi::FormatBool(b).string(), expected);
    };

    auto TEST_ESCAPE  = [](bool b, const std::string &expected) {
        EXPECT_EQ(lexi::FormatBool(b).escape(), expected);
    };
    auto TEST_JSONIFY  = [](bool b, const std::string &expected) {
        EXPECT_EQ(lexi::FormatBool(b).escape(), expected);
    };

    TEST_BOOL(true, "true");
    TEST_BOOL(false, "false");
    TEST_CONST_BOOL(true, "true");
    TEST_CONST_BOOL(false, "false");
    TEST_VOLATILE_BOOL(true, "true");
    TEST_VOLATILE_BOOL(false, "false");
    TEST_CV_BOOL(true, "true");
    TEST_CV_BOOL(false, "false");
    TEST_ESCAPE(false, "false");
    TEST_JSONIFY(false, "false");
}
