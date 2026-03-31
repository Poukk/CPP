#include <gtest/gtest.h>

#include <cmath>

#include "Fixed.hpp"

namespace {

float quantize(float value) {
    return std::roundf(value * 256.0f) / 256.0f;
}

}  // namespace

class Module02Ex02FixedFixture : public ::testing::Test {
   protected:
    Fixed smaller_{1.5f};
    Fixed larger_{2.5f};
    Fixed equal_left_{3};
    Fixed equal_right_{3};
    Fixed zero_{0};
    Fixed negative_{-3.5f};
};

TEST(Module02Ex02FixedUnitTest, OperatorGreaterReturnsTrueWhenFirstIsGreater) {
    EXPECT_TRUE(Fixed(3) > Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorGreaterReturnsFalseWhenFirstIsLessOrEqual) {
    EXPECT_FALSE(Fixed(2) > Fixed(2));
    EXPECT_FALSE(Fixed(1) > Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorLessReturnsTrueWhenFirstIsLess) {
    EXPECT_TRUE(Fixed(1) < Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorLessReturnsFalseWhenFirstIsGreaterOrEqual) {
    EXPECT_FALSE(Fixed(2) < Fixed(2));
    EXPECT_FALSE(Fixed(3) < Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorGreaterOrEqualReturnsTrueWhenFirstIsGreaterOrEqual) {
    EXPECT_TRUE(Fixed(3) >= Fixed(2));
    EXPECT_TRUE(Fixed(2) >= Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorGreaterOrEqualReturnsFalseWhenFirstIsLess) {
    EXPECT_FALSE(Fixed(1) >= Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorLessOrEqualReturnsTrueWhenFirstIsLessOrEqual) {
    EXPECT_TRUE(Fixed(1) <= Fixed(2));
    EXPECT_TRUE(Fixed(2) <= Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorLessOrEqualReturnsFalseWhenFirstIsGreater) {
    EXPECT_FALSE(Fixed(3) <= Fixed(2));
}

TEST(Module02Ex02FixedUnitTest, OperatorEqualReturnsTrueWhenValuesEqual) {
    EXPECT_TRUE(Fixed(2.5f) == Fixed(2.5f));
}

TEST(Module02Ex02FixedUnitTest, OperatorEqualReturnsFalseWhenValuesDiffer) {
    EXPECT_FALSE(Fixed(2.5f) == Fixed(2.25f));
}

TEST(Module02Ex02FixedUnitTest, OperatorNotEqualReturnsTrueWhenValuesDiffer) {
    EXPECT_TRUE(Fixed(2.5f) != Fixed(2.25f));
}

TEST(Module02Ex02FixedUnitTest, OperatorNotEqualReturnsFalseWhenValuesEqual) {
    EXPECT_FALSE(Fixed(2.5f) != Fixed(2.5f));
}

TEST(Module02Ex02FixedUnitTest, OperatorPlusAddsTwoFixedValuesCorrectly) {
    const Fixed result = Fixed(5.5f) + Fixed(2.25f);

    EXPECT_FLOAT_EQ(result.toFloat(), 7.75f);
}

TEST(Module02Ex02FixedUnitTest, OperatorMinusSubtractsTwoFixedValuesCorrectly) {
    const Fixed result = Fixed(5.5f) - Fixed(2.25f);

    EXPECT_FLOAT_EQ(result.toFloat(), 3.25f);
}

TEST(Module02Ex02FixedUnitTest, OperatorMultiplyMultipliesTwoFixedValuesCorrectly) {
    const Fixed result = Fixed(5.05f) * Fixed(2);

    EXPECT_FLOAT_EQ(result.toFloat(), 10.1015625f);
}

TEST(Module02Ex02FixedUnitTest, OperatorDivideDividesTwoFixedValuesCorrectly) {
    const Fixed result = Fixed(10.5f) / Fixed(2);

    EXPECT_FLOAT_EQ(result.toFloat(), 5.25f);
}

TEST(Module02Ex02FixedUnitTest, DivisionByZeroTerminatesBecauseNoHandlingExists) {
    EXPECT_DEATH(
        {
            Fixed numerator(1);
            Fixed denominator(0);
            const Fixed result = numerator / denominator;
            (void)result;
        },
        "");
}

TEST(Module02Ex02FixedUnitTest, PreIncrementIncrementsValueAndReturnsReference) {
    Fixed value;
    Fixed &result = ++value;

    EXPECT_EQ(&result, &value);
    EXPECT_FLOAT_EQ(value.toFloat(), 1.0f / 256.0f);
}

TEST(Module02Ex02FixedUnitTest, PostIncrementReturnsOriginalValueThenIncrements) {
    Fixed value;
    const Fixed original = value++;

    EXPECT_FLOAT_EQ(original.toFloat(), 0.0f);
    EXPECT_FLOAT_EQ(value.toFloat(), 1.0f / 256.0f);
}

TEST(Module02Ex02FixedUnitTest, PreDecrementDecrementsValueAndReturnsReference) {
    Fixed value;

    ++value;
    ++value;
    Fixed &result = --value;

    EXPECT_EQ(&result, &value);
    EXPECT_FLOAT_EQ(value.toFloat(), 1.0f / 256.0f);
}

TEST(Module02Ex02FixedUnitTest, PostDecrementReturnsOriginalValueThenDecrements) {
    Fixed value;

    ++value;
    ++value;
    const Fixed original = value--;

    EXPECT_FLOAT_EQ(original.toFloat(), 2.0f / 256.0f);
    EXPECT_FLOAT_EQ(value.toFloat(), 1.0f / 256.0f);
}

TEST(Module02Ex02FixedUnitTest, MinReturnsSmallerOfTwoFixedObjects) {
    Fixed left(1.5f);
    Fixed right(2.5f);

    EXPECT_EQ(&Fixed::min(left, right), &left);
}

TEST(Module02Ex02FixedUnitTest, MaxReturnsLargerOfTwoFixedObjects) {
    Fixed left(1.5f);
    Fixed right(2.5f);

    EXPECT_EQ(&Fixed::max(left, right), &right);
}

TEST(Module02Ex02FixedUnitTest, MinWithConstReferencesReturnsSmallerObject) {
    const Fixed left(1.5f);
    const Fixed right(2.5f);

    EXPECT_EQ(&Fixed::min(left, right), &left);
}

TEST(Module02Ex02FixedUnitTest, MaxWithConstReferencesReturnsLargerObject) {
    const Fixed left(1.5f);
    const Fixed right(2.5f);

    EXPECT_EQ(&Fixed::max(left, right), &right);
}

TEST(Module02Ex02FixedUnitTest, ToFloatReturnsCorrectFloatRepresentation) {
    EXPECT_FLOAT_EQ(Fixed(5.05f).toFloat(), quantize(5.05f));
}

TEST(Module02Ex02FixedUnitTest, ToIntReturnsCorrectIntRepresentation) {
    EXPECT_EQ(Fixed(42.42f).toInt(), 42);
}

TEST_F(Module02Ex02FixedFixture, TwoFixedObjectsWithDifferentValuesAreReadyForComparison) {
    EXPECT_TRUE(smaller_ < larger_);
}

TEST_F(Module02Ex02FixedFixture, FixedWithZeroValueIsReadyForBoundaryTesting) {
    EXPECT_EQ(zero_.toInt(), 0);
    EXPECT_FLOAT_EQ(zero_.toFloat(), 0.0f);
}

TEST_F(Module02Ex02FixedFixture, NegativeValuesAreReadyForArithmeticOperations) {
    EXPECT_FLOAT_EQ(negative_.toFloat(), -3.5f);
}
