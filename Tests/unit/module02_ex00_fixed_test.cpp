#include <gtest/gtest.h>

#include <iostream>

#include "Fixed.hpp"
#include "support/stream_redirect.hpp"

class Module02Ex00FixedFixture : public ::testing::Test {
   protected:
    Module02Ex00FixedFixture() : capture_(std::cout), source_() { source_.setRawBits(321); }

    test_support::scoped_output_capture capture_;
    Fixed source_;
};

TEST(Module02Ex00FixedUnitTest, DefaultConstructorInitializesValueToZero) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    EXPECT_EQ(fixed.getRawBits(), 0);
}

TEST(Module02Ex00FixedUnitTest, CopyConstructorCopiesValueCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed source;
    source.setRawBits(42);
    Fixed copy(source);

    EXPECT_EQ(copy.getRawBits(), 42);
}

TEST(Module02Ex00FixedUnitTest, CopyAssignmentOperatorCopiesValueCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed source;
    Fixed assigned;

    source.setRawBits(-123);
    assigned = source;

    EXPECT_EQ(assigned.getRawBits(), -123);
}

TEST(Module02Ex00FixedUnitTest, GetRawBitsReturnsInternalValue) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    fixed.setRawBits(12345);

    EXPECT_EQ(fixed.getRawBits(), 12345);
}

TEST(Module02Ex00FixedUnitTest, SetRawBitsSetsInternalValue) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    fixed.setRawBits(-9876);

    EXPECT_EQ(fixed.getRawBits(), -9876);
}

TEST(Module02Ex00FixedUnitTest, DestructorIsCalledWithoutCrash) {
    test_support::scoped_output_capture capture(std::cout);

    {
        Fixed fixed;
        fixed.setRawBits(7);
    }

    EXPECT_NE(capture.str().find("Destructor called\n"), std::string::npos);
}

TEST_F(Module02Ex00FixedFixture, FixedObjectCreatedWithDefaultConstructor) {
    Fixed fixed;

    EXPECT_EQ(fixed.getRawBits(), 0);
}

TEST_F(Module02Ex00FixedFixture, FixedObjectCreatedViaCopyConstructorFromAnotherFixed) {
    Fixed copy(source_);

    EXPECT_EQ(copy.getRawBits(), source_.getRawBits());
}

TEST_F(Module02Ex00FixedFixture, FixedObjectCreatedViaCopyAssignmentFromAnotherFixed) {
    Fixed assigned;

    assigned = source_;

    EXPECT_EQ(assigned.getRawBits(), source_.getRawBits());
}
