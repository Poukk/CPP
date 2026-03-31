#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"
#include "support/stream_redirect.hpp"

TEST(Module01Ex03WeaponHumanTest, WeaponTypeCanBeMutated) {
    Weapon weapon("club");

    EXPECT_EQ(weapon.getType(), "club");
    weapon.setType("sword");
    EXPECT_EQ(weapon.getType(), "sword");
}

TEST(Module01Ex03WeaponHumanTest, HumanAUsesUpdatedWeaponReference) {
    Weapon club("crude spiked club");
    HumanA bob("Bob", club);
    test_support::scoped_output_capture capture(std::cout);

    bob.attack();
    club.setType("some other type of club");
    bob.attack();

    EXPECT_EQ(capture.str(),
              "Bob attacks with their crude spiked club\n"
              "Bob attacks with their some other type of club\n");
}

TEST(Module01Ex03WeaponHumanTest, HumanBAttacksWithBareHandsUntilWeaponIsAssigned) {
    Weapon club("crude spiked club");
    HumanB jim("Jim");
    test_support::scoped_output_capture capture(std::cout);

    jim.attack();
    jim.setWeapon(club);
    jim.attack();
    club.setType("some other type of club");
    jim.attack();

    EXPECT_EQ(capture.str(),
              "Jim attacks with their bare hands\n"
              "Jim attacks with their crude spiked club\n"
              "Jim attacks with their some other type of club\n");
}
