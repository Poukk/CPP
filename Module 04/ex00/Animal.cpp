#include "Animal.hpp"
#include <iostream>

Animal::Animal(void) : type("Animal") {
  std::cout << "Animal default constructor: type set to " << this->type
            << std::endl;
}

Animal::Animal(const Animal &other) : type(other.type) {
  std::cout << "Animal copy constructor: copied type " << this->type
            << std::endl;
}

Animal &Animal::operator=(const Animal &other) {
  std::cout << "Animal copy assignment operator called" << std::endl;
  if (this != &other)
    this->type = other.type;
  return (*this);
}

Animal::~Animal(void) {
  std::cout << "Animal destructor: destroying type " << this->type
            << std::endl;
}

const std::string &Animal::getType(void) const { return (this->type); }

void Animal::makeSound(void) const {
  std::cout << "Animal sound: indistinct wilderness noises" << std::endl;
}
