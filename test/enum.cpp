//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test enumerated value formatting and extraction.
 */

#include <lexi/enum.hpp>
#include <gtest/gtest.h>

// DATA
// ----

enum class Enumerated: uint32_t
{
    MEMBER = 0,
};

// TESTS
// -----


TEST(FormatEnum, Format)
{
    auto TEST_ENUM  = [](auto t, const std::string &expected) {
        EXPECT_EQ(std::string(lexi::FormatEnum(t)), expected);
    };

    TEST_ENUM(Enumerated::MEMBER, "0");
}
