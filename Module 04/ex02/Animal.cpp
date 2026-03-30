#include "Animal.hpp"
#include <iostream>

Animal::Animal(void) : type("Animal") {
  std::cout << "Animal constructor: abstract animal base initialized"
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
  std::cout << "Animal destructor: abstract animal base destroyed"
            << std::endl;
}

const std::string &Animal::getType(void) const { return (this->type); }
