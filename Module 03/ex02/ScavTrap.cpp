#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(void) : ClapTrap("default") {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap default constructor called for " << this->_name
              << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap constructor called for " << this->_name << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
    std::cout << "ScavTrap copy constructor called for " << this->_name
              << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    if (this != &other)
        ClapTrap::operator=(other);
    return (*this);
}

ScavTrap::~ScavTrap(void) {
    std::cout << "ScavTrap destructor called for " << this->_name << std::endl;
}

void ScavTrap::attack(const std::string &target) {
    if (this->_hitPoints == 0) {
        std::cout << "ScavTrap " << this->_name
                  << " cannot attack because it has no hit points left!"
                  << std::endl;
        return;
    }
    if (this->_energyPoints == 0) {
        std::cout << "ScavTrap " << this->_name
                  << " cannot attack because it has no energy points left!"
                  << std::endl;
        return;
    }
    this->_energyPoints--;
    std::cout << "ScavTrap " << this->_name << " attacks " << target
              << ", causing " << this->_attackDamage
              << " points of damage!" << std::endl;
}

void ScavTrap::guardGate(void) {
    std::cout << "ScavTrap " << this->_name
              << " is now in Gatekeeper mode." << std::endl;
}
