#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"
#include "support/temp_dir.hpp"

TEST(Module01Ex04ReplaceIntegrationTest, MainProgramPrintsUsageWhenArgumentCountIsWrong) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX04_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 1);
    EXPECT_EQ(result.stdout_output, "");
    EXPECT_EQ(result.stderr_output, "Usage: ./replace <filename> <s1> <s2>\n");
}

TEST(Module01Ex04ReplaceIntegrationTest, MainProgramCreatesReplaceFileFromArguments) {
    test_support::scoped_temp_dir temp_dir;
    const std::string input_name = "story.txt";
    const std::string input_path = temp_dir.file_path(input_name);
    std::vector<std::string> args;

    temp_dir.write_file(input_name, "hello world world\n");
    args.push_back(input_path);
    args.push_back("world");
    args.push_back("planet");

    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX04_APP_PATH, args);

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "");
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(temp_dir.read_file(input_name + ".replace"), "hello planet planet\n");
}

TEST(Module01Ex04ReplaceIntegrationTest, MainProgramRejectsEmptySearchString) {
    test_support::scoped_temp_dir temp_dir;
    const std::string input_name = "story.txt";
    const std::string input_path = temp_dir.file_path(input_name);
    std::vector<std::string> args;

    temp_dir.write_file(input_name, "hello world\n");
    args.push_back(input_path);
    args.push_back("");
    args.push_back("planet");

    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX04_APP_PATH, args);

    EXPECT_EQ(result.exit_code, 1);
    EXPECT_EQ(result.stdout_output, "");
    EXPECT_EQ(result.stderr_output, "Error: s1 must not be empty.\n");
}
