#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(void)
    : _name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap default constructor called for " << this->_name
              << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap constructor called for " << this->_name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
    : _name(other._name),
      _hitPoints(other._hitPoints),
      _energyPoints(other._energyPoints),
      _attackDamage(other._attackDamage) {
    std::cout << "ClapTrap copy constructor called for " << this->_name
              << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    std::cout << "ClapTrap copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return (*this);
}

ClapTrap::~ClapTrap(void) {
    std::cout << "ClapTrap destructor called for " << this->_name << std::endl;
}

void ClapTrap::attack(const std::string &target) {
    if (this->_hitPoints == 0) {
        std::cout << "ClapTrap " << this->_name
                  << " cannot attack because it has no hit points left!"
                  << std::endl;
        return;
    }
    if (this->_energyPoints == 0) {
        std::cout << "ClapTrap " << this->_name
                  << " cannot attack because it has no energy points left!"
                  << std::endl;
        return;
    }
    this->_energyPoints--;
    std::cout << "ClapTrap " << this->_name << " attacks " << target
              << ", causing " << this->_attackDamage
              << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->_hitPoints == 0) {
        std::cout << "ClapTrap " << this->_name
                  << " cannot take more damage because it is already destroyed!"
                  << std::endl;
        return;
    }
    if (amount >= this->_hitPoints)
        this->_hitPoints = 0;
    else
        this->_hitPoints -= amount;
    std::cout << "ClapTrap " << this->_name << " takes " << amount
              << " points of damage and now has " << this->_hitPoints
              << " hit points left!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->_hitPoints == 0) {
        std::cout << "ClapTrap " << this->_name
                  << " cannot repair itself because it has no hit points left!"
                  << std::endl;
        return;
    }
    if (this->_energyPoints == 0) {
        std::cout << "ClapTrap " << this->_name
                  << " cannot repair itself because it has no energy points left!"
                  << std::endl;
        return;
    }
    this->_energyPoints--;
    this->_hitPoints += amount;
    std::cout << "ClapTrap " << this->_name << " repairs itself for "
              << amount << " hit points and now has " << this->_hitPoints
              << " hit points!" << std::endl;
}
