#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main(void) {
  std::cout << "===== Animal testing =====" << std::endl;
  const Animal *dog = new Dog();
  const Animal *cat = new Cat();

  dog->makeSound();
  cat->makeSound();

  delete dog;
  delete cat;

  std::cout << "===== Wrong Animal testing =====" << std::endl;
  const WrongAnimal *wrong = new WrongAnimal();
  const WrongAnimal *wrongCat = new WrongCat();

  wrong->makeSound();
  wrongCat->makeSound();

  delete wrong;
  delete wrongCat;

  return (0);
}
