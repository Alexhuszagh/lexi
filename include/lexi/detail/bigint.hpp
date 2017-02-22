//  :copyright: (c) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lexi
 *  \brief Big integer representation.
 */

#pragma once

#include <cstddef>
#include <cstdint>


namespace lexi
{
namespace detail
{
// OBJECTS
// -------


/** \brief Large integer to prevent overflow during calculations.
 */
class BigInteger
{
protected:
    static constexpr size_t bits = 3328;  // 64bit * 54 > 10^1000
    static constexpr size_t capacity = bits / sizeof(uint64_t);

    uint64_t digits_[capacity];
    size_t count_;

    void add(const char *first,
        const char *last);
    static uint64_t parse(const char *first,
        const char *last);
    void push_back(uint64_t digit);

public:
    BigInteger(const BigInteger &other);
    BigInteger & operator=(const BigInteger &other);

    explicit BigInteger(uint64_t digit);
    BigInteger & operator=(uint64_t digit);
    BigInteger(const char *decimals,
        size_t length);

    // PROPERTIES
    size_t count() const;
    uint64_t digit(size_t index) const;
    bool isZero() const;

    // OPERATIONS
    BigInteger & operator+=(uint64_t digit);
    BigInteger & operator*=(uint64_t digit);
    BigInteger & operator*=(uint32_t digit);
    BigInteger & operator<<=(size_t shift);
    bool operator==(const BigInteger &other) const;
    bool operator==(const uint64_t other) const;

    BigInteger & mulPow5(unsigned int exponent);
    int compare(const BigInteger &other) const;
    bool difference(const BigInteger &other,
        BigInteger *out) const;
};

}   /* detail */
}   /* lexi */
