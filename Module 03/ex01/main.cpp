#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(void) {
    std::cout << "--- ClapTrap test ---" << std::endl;
    ClapTrap basic("Basic");
    basic.attack("training dummy");
    basic.takeDamage(4);
    basic.beRepaired(2);
    basic.takeDamage(20);
    basic.attack("training dummy");

    std::cout << std::endl;
    std::cout << "--- ScavTrap chaining test ---" << std::endl;
    {
        ScavTrap guardian("Guardian");
        ScavTrap clone(guardian);
        ScavTrap assigned;

        assigned = guardian;
        guardian.attack("bandit");
        guardian.guardGate();
        guardian.takeDamage(30);
        guardian.beRepaired(15);
        guardian.takeDamage(200);
        guardian.attack("bandit");

        clone.attack("intruder");
        assigned.guardGate();
    }

    return (0);
}
