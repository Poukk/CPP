#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

TEST(Module01Ex03ViolenceIntegrationTest, MainProgramPrintsExpectedAttackSequence) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX03_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(result.stdout_output,
              "Bob attacks with their crude spiked club\n"
              "Bob attacks with their some other type of club\n"
              "Jim attacks with their crude spiked club\n"
              "Jim attacks with their some other type of club\n");
}
