#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

static void printSection(const std::string &title) {
  std::cout << "\n=== " << title << " ===" << std::endl;
}

static void announceAnimal(const Animal &animal) {
  std::cout << "type: " << animal.getType() << std::endl;
  animal.makeSound();
}

static void testPolymorphicBasics(void) {
  printSection("Polymorphic basics with abstract Animal");
  const Animal *dog = new Dog();
  const Animal *cat = new Cat();

  announceAnimal(*dog);
  announceAnimal(*cat);

  delete dog;
  delete cat;
}

static void testAnimalArray(void) {
  printSection("Animal pointer array deletion test");
  const int count = 10;
  Animal *animals[count];

  for (int i = 0; i < count / 2; i++)
    animals[i] = new Dog();
  for (int i = count / 2; i < count; i++)
    animals[i] = new Cat();
  for (int i = 0; i < count; i++)
    announceAnimal(*animals[i]);
  for (int i = 0; i < count; i++)
    delete animals[i];
}

static void testDogDeepCopy(void) {
  printSection("Dog deep copy test");
  Dog original;
  original.setIdea(0, "Protect the house");
  original.setIdea(1, "Chase the ball");

  Dog copy(original);
  Dog assigned;
  assigned = original;

  std::cout << "original brain: " << original.getBrain() << std::endl;
  std::cout << "copy brain: " << copy.getBrain() << std::endl;
  std::cout << "assigned brain: " << assigned.getBrain() << std::endl;
  std::cout << "copy idea[0]: " << copy.getIdea(0) << std::endl;
  std::cout << "assigned idea[1]: " << assigned.getIdea(1) << std::endl;

  original.setIdea(0, "Guard the snacks");
  assigned.setIdea(1, "Sleep near the fireplace");

  std::cout << "original idea[0] after change: " << original.getIdea(0)
            << std::endl;
  std::cout << "copy idea[0] after original change: " << copy.getIdea(0)
            << std::endl;
  std::cout << "original idea[1] after assigned change: " << original.getIdea(1)
            << std::endl;
  std::cout << "assigned idea[1] after change: " << assigned.getIdea(1)
            << std::endl;
}

static void testCatDeepCopy(void) {
  printSection("Cat deep copy test");
  Cat original;
  original.setIdea(0, "Sleep on the keyboard");
  original.setIdea(1, "Knock the vase over");

  Cat copy(original);
  Cat assigned;
  assigned = original;

  std::cout << "original brain: " << original.getBrain() << std::endl;
  std::cout << "copy brain: " << copy.getBrain() << std::endl;
  std::cout << "assigned brain: " << assigned.getBrain() << std::endl;
  std::cout << "copy idea[0]: " << copy.getIdea(0) << std::endl;
  std::cout << "assigned idea[1]: " << assigned.getIdea(1) << std::endl;

  original.setIdea(0, "Claim the warm chair");
  assigned.setIdea(1, "Ignore everyone");

  std::cout << "original idea[0] after change: " << original.getIdea(0)
            << std::endl;
  std::cout << "copy idea[0] after original change: " << copy.getIdea(0)
            << std::endl;
  std::cout << "original idea[1] after assigned change: " << original.getIdea(1)
            << std::endl;
  std::cout << "assigned idea[1] after change: " << assigned.getIdea(1)
            << std::endl;
}

static void testIdeaBounds(void) {
  printSection("Brain bounds test");
  Dog dog;
  Cat cat;

  dog.setIdea(99, "Last valid dog idea");
  cat.setIdea(99, "Last valid cat idea");
  std::cout << "dog idea[99]: " << dog.getIdea(99) << std::endl;
  std::cout << "cat idea[99]: " << cat.getIdea(99) << std::endl;
  dog.setIdea(100, "This should fail");
  cat.getIdea(-1);
}

int main(void) {
  testPolymorphicBasics();
  testAnimalArray();
  testDogDeepCopy();
  testCatDeepCopy();
  testIdeaBounds();
  return (0);
}
