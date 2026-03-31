#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

TEST(Module01Ex00ZombieIntegrationTest, MainProgramPrintsExpectedLifecycleSequence) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(result.stdout_output,
              "Steve: BraiiiiiiinnnzzzZ...\n"
              "Paul: BraiiiiiiinnnzzzZ...\n"
              "Frank: BraiiiiiiinnnzzzZ...\n"
              "Frank is destroyed\n"
              "Paul is destroyed\n"
              "Steve is destroyed\n");
}
