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

TEST(Module02Ex01FixedIntegrationTest, FixedFromFloatOutputsCorrectStringRepresentation) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(1234.4321f);
    std::ostringstream output;

    output << fixed;

    EXPECT_EQ(output.str(), "1234.43");
}

TEST(Module02Ex01FixedIntegrationTest, ToIntReturnsExpectedIntegerForFloatInput) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(42.42f);

    EXPECT_EQ(fixed.toInt(), 42);
}

TEST(Module02Ex01FixedIntegrationTest, ChainOfConstructionsAndAssignmentsMaintainsValues) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed original(123.25f);
    Fixed copy(original);
    Fixed assigned;

    assigned = copy;

    EXPECT_EQ(copy.getRawBits(), original.getRawBits());
    EXPECT_EQ(assigned.getRawBits(), original.getRawBits());
}

TEST(Module02Ex01FixedIntegrationTest, StdoutStreamingWorksCorrectly) {
    test_support::scoped_output_capture capture(std::cout);
    Fixed fixed(5.05f);
    const std::size_t before = capture.str().size();

    std::cout << fixed;

    EXPECT_EQ(capture.str().substr(before), "5.05078");
}
