#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <sstream>

#include "Fixed.hpp"
#include "support/stream_redirect.hpp"

namespace {

float quantize(float value) {
    return std::roundf(value * 256.0f) / 256.0f;
}

}  // namespace

class Module02Ex01FixedFixture : public ::testing::Test {
   protected:
    Module02Ex01FixedFixture()
        : capture_(std::cout), int_fixed_(10), float_fixed_(42.42f), const_fixed_(7.75f), source_(123.25f) {}

    test_support::scoped_output_capture capture_;
    Fixed int_fixed_;
    Fixed float_fixed_;
    const Fixed const_fixed_;
    Fixed source_;
};

TEST(Module02Ex01FixedUnitTest, DefaultConstructorInitializesValueToZero) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    EXPECT_EQ(fixed.getRawBits(), 0);
}

TEST(Module02Ex01FixedUnitTest, IntConstructorConvertsIntToFixedPointCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(10);

    EXPECT_EQ(fixed.getRawBits(), 10 << 8);
}

TEST(Module02Ex01FixedUnitTest, FloatConstructorConvertsFloatToFixedPointCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    const float value = 42.42f;
    Fixed fixed(value);

    EXPECT_EQ(fixed.getRawBits(), static_cast<int>(std::roundf(value * 256.0f)));
}

TEST(Module02Ex01FixedUnitTest, CopyConstructorPreservesValue) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed source(42.42f);
    Fixed copy(source);

    EXPECT_EQ(copy.getRawBits(), source.getRawBits());
}

TEST(Module02Ex01FixedUnitTest, CopyAssignmentOperatorPreservesValue) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed source(10);
    Fixed assigned;

    assigned = source;

    EXPECT_EQ(assigned.getRawBits(), source.getRawBits());
}

TEST(Module02Ex01FixedUnitTest, GetRawBitsReturnsInternalValue) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    fixed.setRawBits(1337);

    EXPECT_EQ(fixed.getRawBits(), 1337);
}

TEST(Module02Ex01FixedUnitTest, SetRawBitsSetsInternalValue) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    fixed.setRawBits(-2048);

    EXPECT_EQ(fixed.getRawBits(), -2048);
}

TEST(Module02Ex01FixedUnitTest, ToFloatConvertsFixedPointToFloatCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed;

    fixed.setRawBits(384);

    EXPECT_FLOAT_EQ(fixed.toFloat(), 1.5f);
}

TEST(Module02Ex01FixedUnitTest, ToIntConvertsFixedPointToIntCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(42.42f);

    EXPECT_EQ(fixed.toInt(), 42);
}

TEST(Module02Ex01FixedUnitTest, OstreamOperatorOutputsCorrectFloatRepresentation) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(42.42f);
    std::ostringstream output;

    output << fixed;

    EXPECT_EQ(output.str(), "42.4219");
}

TEST(Module02Ex01FixedUnitTest, ToFloatPreservesExpectedPrecisionForVariousDecimalValues) {
    test_support::scoped_output_capture capture(std::cout);
    const float values[] = {0.5f, 5.05f, -12.75f, 1234.4321f};

    for (std::size_t index = 0; index < sizeof(values) / sizeof(values[0]); ++index) {
        Fixed fixed(values[index]);

        EXPECT_FLOAT_EQ(fixed.toFloat(), quantize(values[index]));
    }
}

TEST(Module02Ex01FixedUnitTest, ToIntTruncatesInsteadOfRoundingDecimalPart) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(42.99f);

    EXPECT_EQ(fixed.toInt(), 42);
}

TEST_F(Module02Ex01FixedFixture, FixedFromIntegerValue) {
    EXPECT_EQ(int_fixed_.getRawBits(), 10 << 8);
    EXPECT_EQ(int_fixed_.toInt(), 10);
}

TEST_F(Module02Ex01FixedFixture, FixedFromFloatValue) {
    EXPECT_FLOAT_EQ(float_fixed_.toFloat(), quantize(42.42f));
}

TEST_F(Module02Ex01FixedFixture, ConstFixedObject) {
    EXPECT_FLOAT_EQ(const_fixed_.toFloat(), 7.75f);
    EXPECT_EQ(const_fixed_.toInt(), 7);
}

TEST_F(Module02Ex01FixedFixture, FixedCreatedFromAnotherFixed) {
    Fixed copy(source_);

    EXPECT_EQ(copy.getRawBits(), source_.getRawBits());
}
