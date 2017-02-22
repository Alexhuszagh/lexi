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
    auto TEST_NULL  = [](std::nullptr_t nullp, const std::string &expected) {
        EXPECT_EQ(std::string(lexi::FormatNull(nullp)), expected);
    };

    TEST_NULL(0, "null");
    TEST_NULL(NULL, "null");
    TEST_NULL(nullptr, "null");
    TEST_NULL(std::nullptr_t(), "null");
}
