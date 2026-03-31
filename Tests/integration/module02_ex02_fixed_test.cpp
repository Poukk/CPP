#include <gtest/gtest.h>

#include <sstream>

#include "Fixed.hpp"

TEST(Module02Ex02FixedIntegrationTest, PostIncrementStreamingSequenceMatchesExample) {
    Fixed a;
    const Fixed b(Fixed(5.05f) * Fixed(2));
    std::ostringstream output;

    output << a << '\n';
    output << ++a << '\n';
    output << a << '\n';
    output << a++ << '\n';
    output << a << '\n';
    output << b << '\n';
    output << Fixed::max(a, b) << '\n';

    EXPECT_EQ(output.str(),
              "0\n"
              "0.00390625\n"
              "0.00390625\n"
              "0.00390625\n"
              "0.0078125\n"
              "10.1016\n"
              "10.1016\n");
}

TEST(Module02Ex02FixedIntegrationTest, PreIncrementOutputsIncrementedValue) {
    Fixed a;
    std::ostringstream output;

    output << ++a;

    EXPECT_EQ(output.str(), "0.00390625");
}

TEST(Module02Ex02FixedIntegrationTest, MaxReturnsCorrectMaximumValue) {
    const Fixed a;
    const Fixed b(Fixed(5.05f) * Fixed(2));

    EXPECT_FLOAT_EQ(Fixed::max(a, b).toFloat(), 10.1015625f);
}

TEST(Module02Ex02FixedIntegrationTest, ComplexMultiplicationExpressionProducesExpectedResult) {
    const Fixed result = Fixed(5.05f) * Fixed(2);

    EXPECT_FLOAT_EQ(result.toFloat(), 10.1015625f);
}

TEST(Module02Ex02FixedIntegrationTest, ArithmeticChainProducesExpectedResult) {
    const Fixed result = Fixed(5.5f) + Fixed(2.25f) - Fixed(1.5f) * Fixed(2);

    EXPECT_FLOAT_EQ(result.toFloat(), 4.75f);
}

TEST(Module02Ex02FixedIntegrationTest, DivisionProducesCorrectDecimalResults) {
    const Fixed result = Fixed(7.5f) / Fixed(2.5f);

    EXPECT_FLOAT_EQ(result.toFloat(), 3.0f);
}
