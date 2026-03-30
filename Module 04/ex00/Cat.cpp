#include "Cat.hpp"
#include <iostream>

Cat::Cat(void) {
  this->type = "Cat";
  std::cout << "Cat default constructor: curious feline awakened"
            << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other) {
  std::cout << "Cat copy constructor: copied a " << this->type << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
  std::cout << "Cat copy assignment operator called" << std::endl;
  if (this != &other)
    Animal::operator=(other);
  return (*this);
}

Cat::~Cat(void) {
  std::cout << "Cat destructor: the purring has stopped" << std::endl;
}

void Cat::makeSound(void) const {
  std::cout << "Cat sound: Meow meow!" << std::endl;
}
