#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <type_traits>

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "support/stream_redirect.hpp"

namespace {

class ScavTrapProbe : public ScavTrap {
   public:
    ScavTrapProbe() : ScavTrap() {}
    explicit ScavTrapProbe(const std::string &name) : ScavTrap(name) {}

    unsigned int hit_points() const { return _hitPoints; }
    unsigned int energy_points() const { return _energyPoints; }
    unsigned int attack_damage() const { return _attackDamage; }
};

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(Module03Ex01ScavTrapUnitTest, PublicInheritanceIsPresent) {
    EXPECT_TRUE((std::is_base_of<ClapTrap, ScavTrap>::value));
}

TEST(Module03Ex01ScavTrapUnitTest, ConstructorInitializesExpectedStats) {
    test_support::scoped_output_capture capture(std::cout);
    ScavTrapProbe trap("Guardian");

    EXPECT_EQ(trap.hit_points(), 100u);
    EXPECT_EQ(trap.energy_points(), 50u);
    EXPECT_EQ(trap.attack_damage(), 20u);
}

TEST(Module03Ex01ScavTrapUnitTest, AttackUsesDerivedMessageAndConsumesEnergy) {
    test_support::scoped_output_capture capture(std::cout);
    ScavTrapProbe trap("Guardian");

    trap.attack("bandit");

    EXPECT_EQ(trap.energy_points(), 49u);
    expect_contains(capture.str(), "ScavTrap Guardian attacks bandit, causing 20 points of damage!");
}

TEST(Module03Ex01ScavTrapUnitTest, InheritedDamageAndRepairUpdateStats) {
    test_support::scoped_output_capture capture(std::cout);
    ScavTrapProbe trap("Guardian");

    trap.takeDamage(30);
    trap.beRepaired(15);

    EXPECT_EQ(trap.hit_points(), 85u);
    EXPECT_EQ(trap.energy_points(), 49u);
    expect_contains(capture.str(), "ClapTrap Guardian takes 30 points of damage and now has 70 hit points left!");
    expect_contains(capture.str(), "ClapTrap Guardian repairs itself for 15 hit points and now has 85 hit points!");
}

TEST(Module03Ex01ScavTrapUnitTest, GuardGatePrintsExpectedMessage) {
    test_support::scoped_output_capture capture(std::cout);
    ScavTrapProbe trap("Guardian");

    trap.guardGate();

    expect_contains(capture.str(), "ScavTrap Guardian is now in Gatekeeper mode.");
}

TEST(Module03Ex01ScavTrapUnitTest, CopyOperationsPreserveDerivedState) {
    test_support::scoped_output_capture capture(std::cout);
    ScavTrapProbe source("Guardian");

    source.attack("intruder");
    source.takeDamage(20);

    ScavTrapProbe copy(source);
    ScavTrapProbe assigned;
    assigned = source;

    EXPECT_EQ(copy.hit_points(), 80u);
    EXPECT_EQ(copy.energy_points(), 49u);
    EXPECT_EQ(copy.attack_damage(), 20u);
    EXPECT_EQ(assigned.hit_points(), 80u);
    EXPECT_EQ(assigned.energy_points(), 49u);
    EXPECT_EQ(assigned.attack_damage(), 20u);
    expect_contains(capture.str(), "ScavTrap copy constructor called for Guardian");
    expect_contains(capture.str(), "ScavTrap copy assignment operator called");
}

TEST(Module03Ex01ScavTrapUnitTest, ConstructionAndDestructionOrderIsChainedCorrectly) {
    test_support::scoped_output_capture capture(std::cout);

    {
        ScavTrapProbe trap("Guardian");
    }

    const std::string output = capture.str();
    const std::string clap_ctor = "ClapTrap constructor called for Guardian";
    const std::string scav_ctor = "ScavTrap constructor called for Guardian";
    const std::string scav_dtor = "ScavTrap destructor called for Guardian";
    const std::string clap_dtor = "ClapTrap destructor called for Guardian";

    ASSERT_NE(output.find(clap_ctor), std::string::npos);
    ASSERT_NE(output.find(scav_ctor), std::string::npos);
    ASSERT_NE(output.find(scav_dtor), std::string::npos);
    ASSERT_NE(output.find(clap_dtor), std::string::npos);
    EXPECT_LT(output.find(clap_ctor), output.find(scav_ctor));
    EXPECT_LT(output.find(scav_dtor), output.find(clap_dtor));
}
