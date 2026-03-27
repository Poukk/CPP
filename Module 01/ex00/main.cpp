#include "Zombie.hpp"

int main() {
    Zombie stackZombie("Steve");
    Zombie *heapZombie = newZombie("Paul");

    stackZombie.announce();
    heapZombie->announce();
    randomChump("Frank");
    delete heapZombie;
    return 0;
}
