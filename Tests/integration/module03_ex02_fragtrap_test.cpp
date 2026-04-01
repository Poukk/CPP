#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(Module03Ex02FragTrapIntegrationTest, MainProgramShowsScavTrapSectionBehavior) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX02_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "ScavTrap Guardian attacks bandit, causing 20 points of damage!");
    expect_contains(result.stdout_output, "ScavTrap Guardian is now in Gatekeeper mode.");
    expect_contains(result.stdout_output, "ScavTrap Guardian cannot attack because it has no hit points left!");
}

TEST(Module03Ex02FragTrapIntegrationTest, MainProgramShowsFragTrapSpecialAbilityAndAttack) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX02_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "ClapTrap Striker attacks boss bot, causing 30 points of damage!");
    expect_contains(result.stdout_output, "FragTrap Striker requests a positive high five!");
}

TEST(Module03Ex02FragTrapIntegrationTest, MainProgramShowsFragTrapConstructionAndDestructionChaining) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX02_APP_PATH, std::vector<std::string>());
    const std::string clap_ctor = "ClapTrap constructor called for Striker";
    const std::string frag_ctor = "FragTrap constructor called for Striker";
    const std::string frag_dtor = "FragTrap destructor called for Striker";
    const std::string clap_dtor = "ClapTrap destructor called for Striker";

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    ASSERT_NE(result.stdout_output.find(clap_ctor), std::string::npos);
    ASSERT_NE(result.stdout_output.find(frag_ctor), std::string::npos);
    ASSERT_NE(result.stdout_output.rfind(frag_dtor), std::string::npos);
    ASSERT_NE(result.stdout_output.rfind(clap_dtor), std::string::npos);
    EXPECT_LT(result.stdout_output.find(clap_ctor), result.stdout_output.find(frag_ctor));
    EXPECT_LT(result.stdout_output.rfind(frag_dtor), result.stdout_output.rfind(clap_dtor));
}
