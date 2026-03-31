#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../../Module 01/ex00/Zombie.hpp"
#include "support/stream_redirect.hpp"

TEST(Module01Ex00ZombieTest, DefaultZombieCanBeRenamedBeforeAnnouncement) {
    Zombie zombie;
    test_support::scoped_output_capture capture(std::cout);

    zombie.setName("Walker");
    zombie.announce();

    EXPECT_EQ(capture.str(), "Walker: BraiiiiiiinnnzzzZ...\n");
}

TEST(Module01Ex00ZombieTest, NewZombieUsesRequestedNameAndPrintsDestructorMessage) {
    test_support::scoped_output_capture capture(std::cout);
    Zombie *zombie = newZombie("Paul");

    zombie->announce();
    delete zombie;

    EXPECT_EQ(capture.str(),
              "Paul: BraiiiiiiinnnzzzZ...\n"
              "Paul is destroyed\n");
}

TEST(Module01Ex00ZombieTest, RandomChumpAnnouncesAndDestroysStackZombieImmediately) {
    test_support::scoped_output_capture capture(std::cout);

    randomChump("Frank");

    EXPECT_EQ(capture.str(),
              "Frank: BraiiiiiiinnnzzzZ...\n"
              "Frank is destroyed\n");
}
