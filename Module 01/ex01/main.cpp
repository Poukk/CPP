#include "Zombie.hpp"

#include <cstdlib>
#include <iostream>

static void announceHorde(Zombie *horde, int count) {
    int i;

    i = 0;
    while (i < count) {
        horde[i].announce();
        i++;
    }
}

int main() {
    const int hordeSize = 5;
    Zombie *horde = zombieHorde(hordeSize, "Walker");

    if (horde == 0) {
        std::cerr << "Failed to allocate zombie horde" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Testing zombieHorde with " << hordeSize << " zombies"
              << std::endl;
    announceHorde(horde, hordeSize);
    delete[] horde;
    return EXIT_SUCCESS;
}
