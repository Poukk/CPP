#include "Cat.hpp"
#include <iostream>

Cat::Cat(void) {
  this->type = "Cat";
  std::cout << "Cat default constructor" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other) {
  std::cout << "Cat copy constructor" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
  std::cout << "Cat copy assignment operator called" << std::endl;
  if (this != &other)
    Animal::operator=(other);
  return (*this);
}

Cat::~Cat(void) {
  std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound(void) const {
  std::cout << "Meow meow!" << std::endl;
}
