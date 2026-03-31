#include <gtest/gtest.h>

#include <iostream>

#include "Fixed.hpp"
#include "support/stream_redirect.hpp"

TEST(Module02Ex00FixedIntegrationTest, ChainOfCopyOperationsMaintainsValueIntegrity) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed a;
    Fixed b;
    Fixed c;

    a.setRawBits(99);
    b = a;
    c = b;

    EXPECT_EQ(a.getRawBits(), 99);
    EXPECT_EQ(b.getRawBits(), 99);
    EXPECT_EQ(c.getRawBits(), 99);
}

TEST(Module02Ex00FixedIntegrationTest, GetRawBitsReturnsCorrectValueAfterSetRawBits) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    fixed.setRawBits(-256);

    EXPECT_EQ(fixed.getRawBits(), -256);
}

TEST(Module02Ex00FixedIntegrationTest, MultipleFixedObjectsCoexistWithoutInterference) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed first;
    Fixed second;
    Fixed third;

    first.setRawBits(1);
    second.setRawBits(2);
    third.setRawBits(3);

    EXPECT_EQ(first.getRawBits(), 1);
    EXPECT_EQ(second.getRawBits(), 2);
    EXPECT_EQ(third.getRawBits(), 3);
}
