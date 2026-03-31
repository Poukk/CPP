#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "Harl.hpp"
#include "support/process_runner.hpp"

TEST(Module01Ex05HarlIntegrationTest, MainProgramPrintsAllComplaintLevelsInOrder) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX05_APP_PATH, std::vector<std::string>());
    const std::string expected =
        std::string(HARL_DEBUG) + "\n" +
        HARL_INFO + "\n" +
        HARL_WARNING + "\n" +
        HARL_ERROR + "\n" +
        "[UNKNOWN LOG LEVEL]\n";

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(result.stdout_output, expected);
}
