#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(Module04Ex01BrainIntegrationTest, MainProgramExercisesAnimalSoundsAndDeepCopies) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE04_EX01_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "===== Animal testing =====");
    expect_contains(result.stdout_output, "Woof woof!");
    expect_contains(result.stdout_output, "Meow meow!");
    expect_contains(result.stdout_output, "===== Deep copy testing =====");
    expect_contains(result.stdout_output, "basic idea: Sleep all day");
    expect_contains(result.stdout_output, "copy idea: Protect the house");
    expect_contains(result.stdout_output, "first idea: Take a nap");
    expect_contains(result.stdout_output, "second idea: Catch mice");
}
