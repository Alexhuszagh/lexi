//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test generalized formatting and extraction.
 */

#include <lexi/lexi.hpp>
#include <gtest/gtest.h>

// DATA
// ----

enum class Enumerated: uint32_t
{
    MEMBER = 0,
};


// TESTS
// -----


TEST(Lexi, Format)
{
    EXPECT_EQ(lexi::lexi(nullptr), "null");
    EXPECT_EQ(lexi::lexi(Enumerated::MEMBER), "0");
    EXPECT_EQ(lexi::lexi(true), "true");
    EXPECT_EQ(lexi::lexi(false), "false");
    EXPECT_EQ(lexi::lexi('A'), "A");
    EXPECT_EQ(lexi::lexi('\0'), std::string("\0", 1));
    EXPECT_EQ(lexi::lexi(1), "1");
    EXPECT_EQ(lexi::lexi(1.0), "1.0");
    // TODO: need to check if std::string or convertible
}


TEST(Lexi, Extract)
{
    // TODO: implement...
}
