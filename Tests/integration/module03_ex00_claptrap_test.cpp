#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

int count_occurrences(const std::string &haystack, const std::string &needle) {
    int count = 0;
    std::string::size_type position = 0;

    while ((position = haystack.find(needle, position)) != std::string::npos) {
        ++count;
        position += needle.size();
    }
    return count;
}

}  // namespace

TEST(Module03Ex00ClapTrapIntegrationTest, MainProgramRunsAndPrintsLifecycleEvents) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "ClapTrap constructor called for Alpha");
    expect_contains(result.stdout_output, "ClapTrap constructor called for Beta");
    expect_contains(result.stdout_output, "ClapTrap copy constructor called for Alpha");
    expect_contains(result.stdout_output, "ClapTrap default constructor called for default");
    expect_contains(result.stdout_output, "ClapTrap copy assignment operator called");
}

TEST(Module03Ex00ClapTrapIntegrationTest, MainProgramExercisesDestroyedAndExhaustedPaths) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "ClapTrap Beta takes 10 points of damage and now has 0 hit points left!");
    expect_contains(result.stdout_output, "ClapTrap Beta cannot attack because it has no hit points left!");
    expect_contains(result.stdout_output, "ClapTrap Beta cannot repair itself because it has no hit points left!");
    EXPECT_EQ(count_occurrences(result.stdout_output,
                                "ClapTrap Alpha attacks practice bot, causing 0 points of damage!"),
              10);
    expect_contains(result.stdout_output, "ClapTrap Alpha cannot attack because it has no energy points left!");
    expect_contains(result.stdout_output, "ClapTrap Alpha cannot repair itself because it has no energy points left!");
}

TEST(Module03Ex00ClapTrapIntegrationTest, MainProgramDestroysAllInstancesAtShutdown) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(count_occurrences(result.stdout_output, "ClapTrap destructor called for Alpha"), 2);
    EXPECT_EQ(count_occurrences(result.stdout_output, "ClapTrap destructor called for Beta"), 2);
}
