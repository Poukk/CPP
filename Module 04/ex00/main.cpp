#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

static void printSection(const std::string &title) {
  std::cout << "\n=== " << title << " ===" << std::endl;
}

int main(void) {
  printSection("Basic polymorphism test");
  const Animal *meta = new Animal();
  const Animal *dog = new Dog();
  const Animal *cat = new Cat();

  std::cout << "meta type: " << meta->getType() << std::endl;
  std::cout << "dog type: " << dog->getType() << std::endl;
  std::cout << "cat type: " << cat->getType() << std::endl;
  cat->makeSound();
  dog->makeSound();
  meta->makeSound();

  delete meta;
  delete dog;
  delete cat;

  printSection("Stack instances");
  Animal animal;
  Dog stackDog;
  Cat stackCat;

  std::cout << "animal type: " << animal.getType() << std::endl;
  std::cout << "stackDog type: " << stackDog.getType() << std::endl;
  std::cout << "stackCat type: " << stackCat.getType() << std::endl;
  animal.makeSound();
  stackDog.makeSound();
  stackCat.makeSound();

  printSection("Copy constructor and assignment");
  Dog originalDog;
  Dog copiedDog(originalDog);
  Dog assignedDog;
  assignedDog = originalDog;

  Cat originalCat;
  Cat copiedCat(originalCat);
  Cat assignedCat;
  assignedCat = originalCat;

  std::cout << "copiedDog type: " << copiedDog.getType() << std::endl;
  std::cout << "assignedDog type: " << assignedDog.getType() << std::endl;
  std::cout << "copiedCat type: " << copiedCat.getType() << std::endl;
  std::cout << "assignedCat type: " << assignedCat.getType() << std::endl;

  printSection("Array of base-class pointers");
  Animal *animals[4];
  animals[0] = new Dog();
  animals[1] = new Cat();
  animals[2] = new Dog();
  animals[3] = new Cat();
  for (int i = 0; i < 4; i++) {
    std::cout << "animals[" << i << "] type: " << animals[i]->getType()
              << std::endl;
    animals[i]->makeSound();
  }
  for (int i = 0; i < 4; i++)
    delete animals[i];

  printSection("WrongAnimal demonstration");
  const WrongAnimal *wrongMeta = new WrongAnimal();
  const WrongAnimal *wrongCat = new WrongCat();
  WrongCat directWrongCat;

  std::cout << "wrongMeta type: " << wrongMeta->getType() << std::endl;
  std::cout << "wrongCat type: " << wrongCat->getType() << std::endl;
  wrongMeta->makeSound();
  wrongCat->makeSound();
  directWrongCat.makeSound();

  delete wrongMeta;
  delete wrongCat;

  return (0);
}
