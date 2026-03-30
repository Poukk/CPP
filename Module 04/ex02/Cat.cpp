#include "Cat.hpp"
#include <iostream>

Cat::Cat(void) : brain(new Brain()) {
  this->type = "Cat";
  std::cout << "Cat default constructor: cat brain allocated" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other), brain(new Brain(*other.brain)) {
  std::cout << "Cat copy constructor: deep-copied cat brain" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
  std::cout << "Cat copy assignment operator called" << std::endl;
  if (this != &other) {
    Animal::operator=(other);
    *(this->brain) = *(other.brain);
  }
  return (*this);
}

Cat::~Cat(void) {
  delete this->brain;
  std::cout << "Cat destructor: cat brain deleted" << std::endl;
}

void Cat::makeSound(void) const { std::cout << "Cat sound: Meow!" << std::endl; }

void Cat::setIdea(int index, const std::string &idea) {
  this->brain->setIdea(index, idea);
}

const std::string &Cat::getIdea(int index) const {
  return (this->brain->getIdea(index));
}

const Brain *Cat::getBrain(void) const { return (this->brain); }
