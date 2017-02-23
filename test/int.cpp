//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test integer formatting and extraction.
 */

#include <lexi/int.hpp>
#include <gtest/gtest.h>


// TESTS
// -----


TEST(FormatInt, Unsigned)
{
    auto TEST_USHORT = [](const unsigned short value, const std::string &expected) {
        EXPECT_EQ(lexi::FormatInt(value).escape(), expected);
    };
    auto TEST_UINT = [](const unsigned int value, const std::string &expected) {
        EXPECT_EQ(lexi::FormatInt(value).escape(), expected);
    };
    auto TEST_ULONG = [](const unsigned long value, const std::string &expected) {
        EXPECT_EQ(lexi::FormatInt(value).escape(), expected);
    };
    auto TEST_ULONGLONG = [](const unsigned long long value, const std::string &expected) {
        EXPECT_EQ(lexi::FormatInt(value).escape(), expected);
    };
    auto TEST_ESCAPE = [](const unsigned long long value, const std::string &expected) {
        EXPECT_EQ(lexi::FormatInt(value).escape(), expected);
    };
    auto TEST_JSONIFY = [](const unsigned long long value, const std::string &expected) {
        EXPECT_EQ(lexi::FormatInt(value).jsonify(), expected);
    };

    TEST_USHORT(1, "1");
    TEST_UINT(1, "1");
    TEST_ULONG(1, "1");
    TEST_ULONGLONG(1, "1");
    TEST_ESCAPE(1, "1");
    TEST_JSONIFY(1, "1");
}
