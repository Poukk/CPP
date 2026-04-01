#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

int main(void) {
  std::cout << "===== Animal testing =====" << std::endl;
  const Animal *dog = new Dog();
  const Animal *cat = new Cat();

  dog->makeSound();
  cat->makeSound();

  delete dog;
  delete cat;

  std::cout << "===== Deep copy testing =====" << std::endl;
  Dog basic;
  basic.setIdea(0, "Protect the house");
  Dog copy(basic);

  basic.setIdea(0, "Sleep all day");
  std::cout << "basic idea: " << basic.getIdea(0) << std::endl;
  std::cout << "copy idea: " << copy.getIdea(0) << std::endl;

  Cat first;
  first.setIdea(0, "Catch mice");
  Cat second;
  second = first;

  first.setIdea(0, "Take a nap");
  std::cout << "first idea: " << first.getIdea(0) << std::endl;
  std::cout << "second idea: " << second.getIdea(0) << std::endl;
  return (0);
}
