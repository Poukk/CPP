#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

TEST(MegaphoneIntegrationTest, PrintsFallbackMessageWhenNoArgumentsAreProvided) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE00_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(result.stdout_output, "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n");
}

TEST(MegaphoneIntegrationTest, UppercasesAllArgumentsAndPreservesSpacingBehavior) {
    const test_support::ProcessResult result = test_support::run_process(
        MODULE00_EX00_APP_PATH, std::vector<std::string>(1, "Hello"));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "HELLO \n");
}

TEST(MegaphoneIntegrationTest, HandlesMultipleMixedCaseArguments) {
    std::vector<std::string> args;
    args.push_back("MiXeD");
    args.push_back("42sp");
    args.push_back("noise!");

    const test_support::ProcessResult result =
        test_support::run_process(MODULE00_EX00_APP_PATH, args);

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "MIXED 42SP NOISE! \n");
}
