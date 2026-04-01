#include "Brain.hpp"
#include <iostream>

Brain::Brain(void) {
  for (int i = 0; i < 100; i++)
    this->ideas[i] = "";
  std::cout << "Brain default constructor" << std::endl;
}

Brain::Brain(const Brain &other) {
  for (int i = 0; i < 100; i++)
    this->ideas[i] = other.ideas[i];
  std::cout << "Brain copy constructor" << std::endl;
}

Brain &Brain::operator=(const Brain &other) {
  std::cout << "Brain copy assignment operator called" << std::endl;
  if (this != &other) {
    for (int i = 0; i < 100; i++)
      this->ideas[i] = other.ideas[i];
  }
  return (*this);
}

Brain::~Brain(void) { std::cout << "Brain destructor" << std::endl; }

void Brain::setIdea(int index, const std::string &idea) {
  if (index < 0 || index >= 100) {
    std::cout << "Brain index out of range" << std::endl;
    return;
  }
  this->ideas[index] = idea;
}

const std::string &Brain::getIdea(int index) const {
  static const std::string emptyIdea = "";

  if (index < 0 || index >= 100) {
    std::cout << "Brain index out of range" << std::endl;
    return (emptyIdea);
  }
  return (this->ideas[index]);
}
