//  :copyright: (c) 2014 Copyright (C)  Milo Yip.
//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test integer formatting and extraction.
 */

#include <lexi/float.hpp>
#include <gtest/gtest.h>

#include <limits>


// TESTS
// -----


TEST(FormatFloat, Iee754)
{
    auto TEST_FLOAT = [](const float value, const std::string &expected) {
        EXPECT_EQ(std::string(lexi::FormatFloat(value)), expected);
    };
    auto TEST_DOUBLE = [](const double value, const std::string &expected) {
        EXPECT_EQ(std::string(lexi::FormatFloat(value)), expected);
    };
    auto TEST_LONGDOUBLE = [](const long double value, const std::string &expected) {
        EXPECT_EQ(std::string(lexi::FormatFloat(value)), expected);
    };

    TEST_FLOAT(0, "0.0");
    TEST_DOUBLE(0, "0.0");
    TEST_LONGDOUBLE(0, "0.0");

    TEST_DOUBLE(1.0, "1.0");
    TEST_DOUBLE(-1.0, "-1.0");
    TEST_DOUBLE(1.2345, "1.2345");
    TEST_DOUBLE(1.2345678, "1.2345678");
    TEST_DOUBLE(0.123456789012, "0.123456789012");
    TEST_DOUBLE(1234567.8, "1234567.8");
    TEST_DOUBLE(-79.39773355813419, "-79.39773355813419");
    TEST_DOUBLE(0.000001, "0.000001");
    TEST_DOUBLE(0.0000001, "1e-7");
    TEST_DOUBLE(1e30, "1e30");
    TEST_DOUBLE(1.234567890123456e30, "1.234567890123456e30");
    TEST_DOUBLE(5e-324, "5e-324");
    TEST_DOUBLE(2.225073858507201e-308, "2.225073858507201e-308");
    TEST_DOUBLE(2.2250738585072014e-308, "2.2250738585072014e-308");
    TEST_DOUBLE(1.7976931348623157e308, "1.7976931348623157e308");

    TEST_DOUBLE(std::numeric_limits<double>::quiet_NaN(), "NaN");
    TEST_DOUBLE(std::numeric_limits<double>::infinity(), "Infinity");
    TEST_DOUBLE(-std::numeric_limits<double>::infinity(), "-Infinity");
}
