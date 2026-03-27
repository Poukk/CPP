#include "Zombie.hpp"

#include <iostream>

Zombie::Zombie() : name("unnamed") {}

Zombie::Zombie(std::string name) : name(name) {}

Zombie::~Zombie() { std::cout << name << " is destroyed" << std::endl; }

void Zombie::announce(void) {
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string zombieName) { name = zombieName; }
