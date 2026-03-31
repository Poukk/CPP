#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

std::vector<std::string> split_lines(const std::string &text) {
    std::vector<std::string> lines;
    std::istringstream stream(text);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.find_first_not_of(' ') != std::string::npos) {
            lines.push_back(line);
        }
    }
    return lines;
}

std::string value_after_colon(const std::string &line) {
    const std::string::size_type position = line.find(':');

    if (position == std::string::npos) {
        return "";
    }

    const std::string value = line.substr(position + 1);
    const std::string::size_type first_content = value.find_first_not_of(' ');

    if (first_content == std::string::npos) {
        return "";
    }
    return value.substr(first_content);
}

}  // namespace

TEST(Module01Ex02BrainIntegrationTest, MainProgramPrintsMatchingAddressesAndValues) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX02_APP_PATH, std::vector<std::string>());
    const std::vector<std::string> lines = split_lines(result.stdout_output);

    ASSERT_EQ(result.exit_code, 0);
    ASSERT_EQ(result.stderr_output, "");
    ASSERT_EQ(lines.size(), 6U);

    EXPECT_FALSE(value_after_colon(lines[0]).empty());
    EXPECT_EQ(value_after_colon(lines[0]), value_after_colon(lines[1]));
    EXPECT_EQ(value_after_colon(lines[0]), value_after_colon(lines[2]));

    EXPECT_EQ(value_after_colon(lines[3]), "HI THIS IS BRAIN");
    EXPECT_EQ(value_after_colon(lines[4]), "HI THIS IS BRAIN");
    EXPECT_EQ(value_after_colon(lines[5]), "HI THIS IS BRAIN");
}
