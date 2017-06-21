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


// TODO: remove

namespace lexi
{

template <typename T>
std::string lexi2(const T &t,
    enable_if_t<!is_string_v<T>, T>* = nullptr)
{
    return Format()(t).string();
}

}   /* lexi:: REMOVE */


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
    EXPECT_EQ(lexi::lexi("1.0"), "1.0");
    EXPECT_EQ(lexi::lexi(std::string("1.0")), "1.0");

    EXPECT_EQ(lexi::escape('\0'), std::string("\\\0", 2));
    EXPECT_EQ(lexi::jsonify('\0'), "\"\\u0000\"");
    EXPECT_EQ(lexi::jsonify('\b'), "\"\\b\"");
    EXPECT_EQ(lexi::jsonify("\b"), "\"\\b\"");
}


TEST(Lexi, Extract)
{
    EXPECT_EQ(lexi::lexi<std::nullptr_t>("null"), nullptr);
//    ASSERT_THROW(lexi::lexi<std::nullptr_t>("false"), std::runtime_error);
    EXPECT_EQ(lexi::lexi<bool>("true"), true);
    EXPECT_EQ(lexi::lexi<bool>("false"), false);
    ASSERT_THROW(lexi::lexi<bool>("null"), std::runtime_error);
    EXPECT_EQ(lexi::lexi<char>("f"), 102);
    EXPECT_EQ(lexi::lexi<unsigned char>("102"), 102);
    ASSERT_THROW(lexi::lexi<char>(""), std::runtime_error);
    EXPECT_EQ(lexi::lexi<unsigned char>(""), 0);
    EXPECT_EQ(lexi::lexi<short>("-1"), -1);
    EXPECT_EQ(lexi::lexi<int>("-1"), -1);
    EXPECT_EQ(lexi::lexi<long>("-1"), -1);
    EXPECT_EQ(lexi::lexi<long long>("-1"), -1);
    EXPECT_EQ(lexi::lexi<unsigned short>("5"), 5);
    EXPECT_EQ(lexi::lexi<unsigned int>("5"), 5);
    EXPECT_EQ(lexi::lexi<unsigned long>("5"), 5);
    EXPECT_EQ(lexi::lexi<unsigned long long>("5"), 5);
    EXPECT_EQ(lexi::lexi<Enumerated>("0"), Enumerated::MEMBER);
    EXPECT_EQ(lexi::lexi("1.0"), "1.0");
    EXPECT_EQ(lexi::lexi(std::string("1.0")), "1.0");
}
