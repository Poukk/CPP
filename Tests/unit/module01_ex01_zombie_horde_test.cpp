#include <gtest/gtest.h>

#include <cstddef>
#include <iostream>
#include <string>

#include "../../Module 01/ex01/Zombie.hpp"
#include "support/stream_redirect.hpp"

namespace {

std::size_t count_occurrences(const std::string &text, const std::string &needle) {
    std::size_t count = 0;
    std::size_t position = 0;

    while ((position = text.find(needle, position)) != std::string::npos) {
        ++count;
        position += needle.length();
    }
    return count;
}

}  // namespace

TEST(Module01Ex01ZombieHordeTest, ReturnsNullForNonPositiveCounts) {
    EXPECT_EQ(zombieHorde(0, "Walker"), static_cast<Zombie *>(0));
    EXPECT_EQ(zombieHorde(-3, "Walker"), static_cast<Zombie *>(0));
}

TEST(Module01Ex01ZombieHordeTest, AllocatedHordeUsesProvidedNameForEveryZombie) {
    Zombie *horde = zombieHorde(3, "Walker");
    test_support::scoped_output_capture capture(std::cout);

    ASSERT_NE(horde, static_cast<Zombie *>(0));
    horde[0].announce();
    horde[1].announce();
    horde[2].announce();
    delete[] horde;

    const std::string output = capture.str();
    EXPECT_EQ(count_occurrences(output, "Walker: BraiiiiiiinnnzzzZ...\n"), 3U);
    EXPECT_EQ(count_occurrences(output, "Walker is destroyed\n"), 3U);
}
