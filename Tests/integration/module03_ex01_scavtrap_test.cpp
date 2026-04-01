#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "support/process_runner.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(Module03Ex01ScavTrapIntegrationTest, MainProgramShowsDerivedAttackAndGateMode) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX01_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "ScavTrap Guardian attacks bandit, causing 20 points of damage!");
    expect_contains(result.stdout_output, "ScavTrap Guardian is now in Gatekeeper mode.");
}

TEST(Module03Ex01ScavTrapIntegrationTest, MainProgramShowsConstructionAndDestructionChaining) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX01_APP_PATH, std::vector<std::string>());
    const std::string clap_ctor = "ClapTrap constructor called for Guardian";
    const std::string scav_ctor = "ScavTrap constructor called for Guardian";
    const std::string scav_dtor = "ScavTrap destructor called for Guardian";
    const std::string clap_dtor = "ClapTrap destructor called for Guardian";

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    ASSERT_NE(result.stdout_output.find(clap_ctor), std::string::npos);
    ASSERT_NE(result.stdout_output.find(scav_ctor), std::string::npos);
    ASSERT_NE(result.stdout_output.rfind(scav_dtor), std::string::npos);
    ASSERT_NE(result.stdout_output.rfind(clap_dtor), std::string::npos);
    EXPECT_LT(result.stdout_output.find(clap_ctor), result.stdout_output.find(scav_ctor));
    EXPECT_LT(result.stdout_output.rfind(scav_dtor), result.stdout_output.rfind(clap_dtor));
}

TEST(Module03Ex01ScavTrapIntegrationTest, MainProgramShowsDestroyedScavTrapCannotAttack) {
    const test_support::ProcessResult result =
        test_support::run_process(MODULE03_EX01_APP_PATH, std::vector<std::string>());

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stderr_output, "");
    expect_contains(result.stdout_output, "ClapTrap Guardian takes 200 points of damage and now has 0 hit points left!");
    expect_contains(result.stdout_output, "ScavTrap Guardian cannot attack because it has no hit points left!");
}
