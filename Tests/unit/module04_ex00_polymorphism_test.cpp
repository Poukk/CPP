#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <type_traits>

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "support/stream_redirect.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

}  // namespace

TEST(Module04Ex00PolymorphismUnitTest, InheritanceAndVirtualDestructionAreDeclared) {
    EXPECT_TRUE((std::is_base_of<Animal, Dog>::value));
    EXPECT_TRUE((std::is_base_of<Animal, Cat>::value));
    EXPECT_TRUE((std::is_base_of<WrongAnimal, WrongCat>::value));
    EXPECT_TRUE((std::has_virtual_destructor<Animal>::value));
}

TEST(Module04Ex00PolymorphismUnitTest, TypesAreInitializedToExpectedValues) {
    Animal animal;
    Dog dog;
    Cat cat;
    WrongAnimal wrong_animal;
    WrongCat wrong_cat;

    EXPECT_EQ(animal.getType(), "Animal");
    EXPECT_EQ(dog.getType(), "Dog");
    EXPECT_EQ(cat.getType(), "Cat");
    EXPECT_EQ(wrong_animal.getType(), "WrongAnimal");
    EXPECT_EQ(wrong_cat.getType(), "WrongCat");
}

TEST(Module04Ex00PolymorphismUnitTest, VirtualDispatchUsesDerivedSoundsThroughAnimalPointers) {
    test_support::scoped_output_capture capture(std::cout);
    const Animal *animals[3] = {new Animal(), new Dog(), new Cat()};

    for (int index = 0; index < 3; ++index) {
        animals[index]->makeSound();
    }
    for (int index = 0; index < 3; ++index) {
        delete animals[index];
    }

    const std::string output = capture.str();
    expect_contains(output, "*generic animal noises*");
    expect_contains(output, "Woof woof!");
    expect_contains(output, "Meow meow!");
}

TEST(Module04Ex00PolymorphismUnitTest, WrongAnimalDispatchUsesBaseImplementationThroughBasePointer) {
    test_support::scoped_output_capture capture(std::cout);
    const WrongAnimal *wrong_cat = new WrongCat();

    wrong_cat->makeSound();
    delete wrong_cat;

    const std::string output = capture.str();
    expect_contains(output, "*wrong generic noise*");
    EXPECT_EQ(output.find("Meow...?"), std::string::npos);
}

TEST(Module04Ex00PolymorphismUnitTest, WrongCatDirectCallStillUsesDerivedImplementation) {
    test_support::scoped_output_capture capture(std::cout);
    WrongCat wrong_cat;

    wrong_cat.makeSound();

    expect_contains(capture.str(), "Meow...?");
}

TEST(Module04Ex00PolymorphismUnitTest, DogConstructionAndDestructionChainBaseClassMessages) {
    test_support::scoped_output_capture capture(std::cout);

    { Dog dog; }

    const std::string output = capture.str();
    const std::string animal_ctor = "Animal default constructor";
    const std::string dog_ctor = "Dog default constructor";
    const std::string dog_dtor = "Dog destructor called";
    const std::string animal_dtor = "Animal destructor";

    ASSERT_NE(output.find(animal_ctor), std::string::npos);
    ASSERT_NE(output.find(dog_ctor), std::string::npos);
    ASSERT_NE(output.rfind(dog_dtor), std::string::npos);
    ASSERT_NE(output.rfind(animal_dtor), std::string::npos);
    EXPECT_LT(output.find(animal_ctor), output.find(dog_ctor));
    EXPECT_LT(output.rfind(dog_dtor), output.rfind(animal_dtor));
}
