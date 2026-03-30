#include "Dog.hpp"
#include <iostream>

Dog::Dog(void) {
  this->type = "Dog";
  std::cout << "Dog default constructor: loyal companion created"
            << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
  std::cout << "Dog copy constructor: copied a " << this->type << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
  std::cout << "Dog copy assignment operator called" << std::endl;
  if (this != &other)
    Animal::operator=(other);
  return (*this);
}

Dog::~Dog(void) {
  std::cout << "Dog destructor: the kennel is now empty" << std::endl;
}

void Dog::makeSound(void) const {
  std::cout << "Dog sound: Woof woof!" << std::endl;
}
