#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

std::size_t count_occurrences(const std::string &text, const std::string &needle) {
    std::size_t count = 0;
    std::size_t position = 0;

    while ((position = text.find(needle, position)) != std::string::npos) {
        ++count;
        position += needle.length();
    }
    return count;
}

}  // namespace

TEST(Module01Ex01ZombieHordeIntegrationTest, MainProgramAnnouncesAndDestroysWholeHorde) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE01_EX01_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_NE(result.stdout_output.find("Testing zombieHorde with 5 zombies\n"), std::string::npos);
    EXPECT_EQ(count_occurrences(result.stdout_output, "Walker: BraiiiiiiinnnzzzZ...\n"), 5U);
    EXPECT_EQ(count_occurrences(result.stdout_output, "Walker is destroyed\n"), 5U);
}
