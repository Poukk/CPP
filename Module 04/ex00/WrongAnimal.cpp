#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal(void) : type("WrongAnimal") {
  std::cout << "WrongAnimal default constructor: confused creature appears"
            << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) : type(other.type) {
  std::cout << "WrongAnimal copy constructor: copied type " << this->type
            << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other) {
  std::cout << "WrongAnimal copy assignment operator called" << std::endl;
  if (this != &other)
    this->type = other.type;
  return (*this);
}

WrongAnimal::~WrongAnimal(void) {
  std::cout << "WrongAnimal destructor: chaotic creature vanishes"
            << std::endl;
}

const std::string &WrongAnimal::getType(void) const { return (this->type); }

void WrongAnimal::makeSound(void) const {
  std::cout << "WrongAnimal sound: puzzling generic noise" << std::endl;
}
