#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <type_traits>

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "support/stream_redirect.hpp"

namespace {

class FragTrapProbe : public FragTrap {
   public:
    FragTrapProbe() : FragTrap() {}
    explicit FragTrapProbe(const std::string &name) : FragTrap(name) {}

    unsigned int hit_points() const { return _hitPoints; }
    unsigned int energy_points() const { return _energyPoints; }
    unsigned int attack_damage() const { return _attackDamage; }
};

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(Module03Ex02FragTrapUnitTest, PublicInheritanceIsPresent) {
    EXPECT_TRUE((std::is_base_of<ClapTrap, FragTrap>::value));
}

TEST(Module03Ex02FragTrapUnitTest, ConstructorInitializesExpectedStats) {
    test_support::scoped_output_capture capture(std::cout);
    FragTrapProbe trap("Striker");

    EXPECT_EQ(trap.hit_points(), 100u);
    EXPECT_EQ(trap.energy_points(), 100u);
    EXPECT_EQ(trap.attack_damage(), 30u);
}

TEST(Module03Ex02FragTrapUnitTest, AttackUsesInheritedClapTrapImplementationWithFragTrapStats) {
    test_support::scoped_output_capture capture(std::cout);
    FragTrapProbe trap("Striker");

    trap.attack("boss bot");

    EXPECT_EQ(trap.energy_points(), 99u);
    expect_contains(capture.str(), "ClapTrap Striker attacks boss bot, causing 30 points of damage!");
}

TEST(Module03Ex02FragTrapUnitTest, TakeDamageAndRepairUpdateState) {
    test_support::scoped_output_capture capture(std::cout);
    FragTrapProbe trap("Striker");

    trap.takeDamage(40);
    trap.beRepaired(10);

    EXPECT_EQ(trap.hit_points(), 70u);
    EXPECT_EQ(trap.energy_points(), 99u);
    expect_contains(capture.str(), "ClapTrap Striker takes 40 points of damage and now has 60 hit points left!");
    expect_contains(capture.str(), "ClapTrap Striker repairs itself for 10 hit points and now has 70 hit points!");
}

TEST(Module03Ex02FragTrapUnitTest, HighFivesGuysPrintsExpectedMessage) {
    test_support::scoped_output_capture capture(std::cout);
    FragTrapProbe trap("Striker");

    trap.highFivesGuys();

    expect_contains(capture.str(), "FragTrap Striker requests a positive high five!");
}

TEST(Module03Ex02FragTrapUnitTest, CopyOperationsPreserveDerivedState) {
    test_support::scoped_output_capture capture(std::cout);
    FragTrapProbe source("Striker");

    source.attack("boss bot");
    source.takeDamage(25);

    FragTrapProbe copy(source);
    FragTrapProbe assigned;
    assigned = source;

    EXPECT_EQ(copy.hit_points(), 75u);
    EXPECT_EQ(copy.energy_points(), 99u);
    EXPECT_EQ(copy.attack_damage(), 30u);
    EXPECT_EQ(assigned.hit_points(), 75u);
    EXPECT_EQ(assigned.energy_points(), 99u);
    EXPECT_EQ(assigned.attack_damage(), 30u);
    expect_contains(capture.str(), "FragTrap copy constructor called for Striker");
    expect_contains(capture.str(), "FragTrap copy assignment operator called");
}

TEST(Module03Ex02FragTrapUnitTest, ConstructionAndDestructionOrderIsChainedCorrectly) {
    test_support::scoped_output_capture capture(std::cout);

    {
        FragTrapProbe trap("Striker");
    }

    const std::string output = capture.str();
    const std::string clap_ctor = "ClapTrap constructor called for Striker";
    const std::string frag_ctor = "FragTrap constructor called for Striker";
    const std::string frag_dtor = "FragTrap destructor called for Striker";
    const std::string clap_dtor = "ClapTrap destructor called for Striker";

    ASSERT_NE(output.find(clap_ctor), std::string::npos);
    ASSERT_NE(output.find(frag_ctor), std::string::npos);
    ASSERT_NE(output.find(frag_dtor), std::string::npos);
    ASSERT_NE(output.find(clap_dtor), std::string::npos);
    EXPECT_LT(output.find(clap_ctor), output.find(frag_ctor));
    EXPECT_LT(output.find(frag_dtor), output.find(clap_dtor));
}
