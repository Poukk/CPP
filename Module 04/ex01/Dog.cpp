#include "Dog.hpp"
#include <iostream>

Dog::Dog(void) : brain(new Brain()) {
  this->type = "Dog";
  std::cout << "Dog default constructor: watchdog and brain allocated"
            << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other), brain(new Brain(*other.brain)) {
  std::cout << "Dog copy constructor: deep-copied dog brain" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
  std::cout << "Dog copy assignment operator called" << std::endl;
  if (this != &other) {
    Animal::operator=(other);
    *(this->brain) = *(other.brain);
  }
  return (*this);
}

Dog::~Dog(void) {
  delete this->brain;
  std::cout << "Dog destructor: dog brain deleted" << std::endl;
}

void Dog::makeSound(void) const { std::cout << "Dog sound: Woof!" << std::endl; }

void Dog::setIdea(int index, const std::string &idea) {
  this->brain->setIdea(index, idea);
}

const std::string &Dog::getIdea(int index) const {
  return (this->brain->getIdea(index));
}

const Brain *Dog::getBrain(void) const { return (this->brain); }
