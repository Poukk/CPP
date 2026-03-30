#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(void) {
    std::cout << "--- ClapTrap test ---" << std::endl;
    ClapTrap basic("Basic");
    basic.attack("training dummy");
    basic.takeDamage(5);
    basic.beRepaired(3);

    std::cout << std::endl;
    std::cout << "--- ScavTrap test ---" << std::endl;
    {
        ScavTrap guardian("Guardian");

        guardian.attack("bandit");
        guardian.guardGate();
        guardian.takeDamage(120);
        guardian.attack("bandit");
    }

    std::cout << std::endl;
    std::cout << "--- FragTrap chaining test ---" << std::endl;
    {
        FragTrap striker("Striker");
        FragTrap clone(striker);
        FragTrap assigned;

        assigned = striker;
        striker.attack("boss bot");
        striker.highFivesGuys();
        striker.takeDamage(40);
        striker.beRepaired(10);
        striker.takeDamage(200);
        striker.highFivesGuys();

        clone.attack("spare target");
        assigned.highFivesGuys();
    }

    return (0);
}
