#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "Harl.hpp"
#include "support/stream_redirect.hpp"

TEST(Module01Ex05HarlTest, ComplainPrintsEveryKnownLevel) {
    const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    const char *messages[] = {HARL_DEBUG, HARL_INFO, HARL_WARNING, HARL_ERROR};
    Harl harl;

    for (int index = 0; index < 4; ++index) {
        test_support::scoped_output_capture capture(std::cout);

        harl.complain(levels[index]);
        EXPECT_EQ(capture.str(), std::string(messages[index]) + "\n");
    }
}

TEST(Module01Ex05HarlTest, UnknownLevelPrintsFallbackMessage) {
    Harl harl;
    test_support::scoped_output_capture capture(std::cout);

    harl.complain("UNKNOWN");

    EXPECT_EQ(capture.str(), "[UNKNOWN LOG LEVEL]\n");
}
