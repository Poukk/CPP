#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

std::vector<std::string> split_lines(const std::string &text) {
    std::vector<std::string> lines;
    std::string current;

    for (std::string::size_type index = 0; index < text.size(); ++index) {
        if (text[index] == '\n') {
            lines.push_back(current);
            current.clear();
        } else {
            current += text[index];
        }
    }
    if (!current.empty()) {
        lines.push_back(current);
    }
    return lines;
}

std::string value_after_colon(const std::string &line) {
    const std::string delimiter = ": ";
    const std::string::size_type position = line.find(delimiter);

    if (position == std::string::npos) {
        return "";
    }
    return line.substr(position + delimiter.length());
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
