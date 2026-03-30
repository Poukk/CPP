#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat(void) {
  this->type = "WrongCat";
  std::cout << "WrongCat default constructor: misleading feline created"
            << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other) {
  std::cout << "WrongCat copy constructor: copied a " << this->type
            << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other) {
  std::cout << "WrongCat copy assignment operator called" << std::endl;
  if (this != &other)
    WrongAnimal::operator=(other);
  return (*this);
}

WrongCat::~WrongCat(void) {
  std::cout << "WrongCat destructor: misleading feline disappears"
            << std::endl;
}

void WrongCat::makeSound(void) const {
  std::cout << "WrongCat sound: Meow...?" << std::endl;
}
