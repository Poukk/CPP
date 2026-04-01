#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "ClapTrap.hpp"
#include "support/stream_redirect.hpp"

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

TEST(Module03Ex00ClapTrapUnitTest, ConstructorAndAttackUseExpectedDefaults) {
    test_support::scoped_output_capture capture(std::cout);
    ClapTrap clap("Alpha");

    clap.attack("target dummy");

    const std::string output = capture.str();
    expect_contains(output, "ClapTrap constructor called for Alpha");
    expect_contains(output, "ClapTrap Alpha attacks target dummy, causing 0 points of damage!");
}

TEST(Module03Ex00ClapTrapUnitTest, TakeDamageAndRepairUpdateObservableHitPoints) {
    test_support::scoped_output_capture capture(std::cout);
    ClapTrap clap("Alpha");

    clap.takeDamage(3);
    clap.beRepaired(2);

    const std::string output = capture.str();
    expect_contains(output, "ClapTrap Alpha takes 3 points of damage and now has 7 hit points left!");
    expect_contains(output, "ClapTrap Alpha repairs itself for 2 hit points and now has 9 hit points!");
}

TEST(Module03Ex00ClapTrapUnitTest, DestroyedClapTrapCannotAttackOrRepair) {
    test_support::scoped_output_capture capture(std::cout);
    ClapTrap clap("Beta");

    clap.takeDamage(10);
    clap.attack("Alpha");
    clap.beRepaired(1);

    const std::string output = capture.str();
    expect_contains(output, "ClapTrap Beta takes 10 points of damage and now has 0 hit points left!");
    expect_contains(output, "ClapTrap Beta cannot attack because it has no hit points left!");
    expect_contains(output, "ClapTrap Beta cannot repair itself because it has no hit points left!");
}

TEST(Module03Ex00ClapTrapUnitTest, EnergyExhaustionBlocksFurtherActionsAfterTenSuccessfulActions) {
    test_support::scoped_output_capture capture(std::cout);
    ClapTrap clap("Alpha");

    for (int index = 0; index < 10; ++index) {
        clap.attack("dummy");
    }
    clap.attack("dummy");
    clap.beRepaired(1);

    const std::string output = capture.str();
    EXPECT_EQ(count_occurrences(output,
                                "ClapTrap Alpha attacks dummy, causing 0 points of damage!"),
              10);
    expect_contains(output, "ClapTrap Alpha cannot attack because it has no energy points left!");
    expect_contains(output, "ClapTrap Alpha cannot repair itself because it has no energy points left!");
}

TEST(Module03Ex00ClapTrapUnitTest, CopyOperationsPreserveCurrentState) {
    test_support::scoped_output_capture capture(std::cout);
    {
        ClapTrap source("Unit");

        source.takeDamage(4);
        source.beRepaired(1);

        ClapTrap copy(source);
        ClapTrap assigned;
        assigned = source;

        copy.takeDamage(3);
        assigned.beRepaired(1);
    }

    const std::string output = capture.str();
    expect_contains(output, "ClapTrap copy constructor called for Unit");
    expect_contains(output, "ClapTrap copy assignment operator called");
    expect_contains(output, "ClapTrap Unit takes 3 points of damage and now has 4 hit points left!");
    expect_contains(output, "ClapTrap Unit repairs itself for 1 hit points and now has 8 hit points!");
    EXPECT_EQ(count_occurrences(output, "ClapTrap destructor called for Unit"), 3);
}
