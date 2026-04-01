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

TEST(Module04Ex00PolymorphismIntegrationTest, MainProgramExercisesExpectedSectionsAndSounds) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE04_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "===== Animal testing =====");
    expect_contains(result.stdout_output, "===== Wrong Animal testing =====");
    expect_contains(result.stdout_output, "Woof woof!");
    expect_contains(result.stdout_output, "Meow meow!");
    expect_contains(result.stdout_output, "*wrong generic noise*");
}

TEST(Module04Ex00PolymorphismIntegrationTest, WrongAnimalSectionShowsFailedPolymorphism) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE04_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    EXPECT_EQ(count_occurrences(result.stdout_output, "*wrong generic noise*"), 2);
    EXPECT_EQ(result.stdout_output.find("Meow...?"), std::string::npos);
}

TEST(Module04Ex00PolymorphismIntegrationTest, MainProgramShowsConstructionAndDestructionMessages) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE04_EX00_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "Animal default constructor");
    expect_contains(result.stdout_output, "Dog default constructor");
    expect_contains(result.stdout_output, "Cat default constructor");
    expect_contains(result.stdout_output, "WrongAnimal default constructor");
    expect_contains(result.stdout_output, "WrongCat default constructor");
    expect_contains(result.stdout_output, "Dog destructor called");
    expect_contains(result.stdout_output, "Cat destructor called");
}
