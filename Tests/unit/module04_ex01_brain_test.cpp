#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <type_traits>

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "support/stream_redirect.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

int count_occurrences(const std::string &haystack, const std::string &needle) {
    int count = 0;
    std::string::size_type position = 0;

    while ((position = haystack.find(needle, position)) != std::string::npos) {
        ++count;
        position += needle.size();
    }
    return count;
}

}  // namespace

TEST(Module04Ex01BrainUnitTest, InheritanceAndVirtualDestructionMatchTheSubject) {
    EXPECT_TRUE((std::is_base_of<Animal, Dog>::value));
    EXPECT_TRUE((std::is_base_of<Animal, Cat>::value));
    EXPECT_TRUE((std::has_virtual_destructor<Animal>::value));
}

TEST(Module04Ex01BrainUnitTest, BrainStartsWithOneHundredEmptyIdeas) {
    Brain brain;

    for (int index = 0; index < 100; ++index) {
        EXPECT_EQ(brain.getIdea(index), "");
    }
}

TEST(Module04Ex01BrainUnitTest, DogAndCatAllocateTheirOwnBrains) {
    Dog dog;
    Cat cat;

    ASSERT_NE(dog.getBrain(), static_cast<const Brain *>(0));
    ASSERT_NE(cat.getBrain(), static_cast<const Brain *>(0));
    EXPECT_NE(dog.getBrain(), cat.getBrain());
    EXPECT_EQ(dog.getType(), "Dog");
    EXPECT_EQ(cat.getType(), "Cat");
}

TEST(Module04Ex01BrainUnitTest, DogCopyConstructorPerformsDeepCopy) {
    Dog original;
    original.setIdea(0, "Protect the house");
    original.setIdea(1, "Chase squirrels");

    Dog copy(original);
    original.setIdea(0, "Sleep all day");

    EXPECT_NE(original.getBrain(), copy.getBrain());
    EXPECT_EQ(original.getIdea(0), "Sleep all day");
    EXPECT_EQ(copy.getIdea(0), "Protect the house");
    EXPECT_EQ(copy.getIdea(1), "Chase squirrels");
}

TEST(Module04Ex01BrainUnitTest, CatAssignmentOperatorPerformsDeepCopy) {
    Cat source;
    Cat assigned;

    source.setIdea(0, "Catch mice");
    source.setIdea(1, "Watch birds");
    assigned = source;
    source.setIdea(0, "Take a nap");

    EXPECT_NE(source.getBrain(), assigned.getBrain());
    EXPECT_EQ(source.getIdea(0), "Take a nap");
    EXPECT_EQ(assigned.getIdea(0), "Catch mice");
    EXPECT_EQ(assigned.getIdea(1), "Watch birds");
}

TEST(Module04Ex01BrainUnitTest, DeletingAnimalsThroughBasePointersDestroysBrainsAndDerivedObjects) {
    test_support::scoped_output_capture capture(std::cout);
    Animal *animals[4] = {new Dog(), new Cat(), new Dog(), new Cat()};

    for (int index = 0; index < 4; ++index) {
        delete animals[index];
    }

    const std::string output = capture.str();
    EXPECT_EQ(count_occurrences(output, "Brain destructor"), 4);
    EXPECT_EQ(count_occurrences(output, "Animal destructor"), 4);
    EXPECT_EQ(count_occurrences(output, "Dog destructor called"), 2);
    EXPECT_EQ(count_occurrences(output, "Cat destructor called"), 2);
    expect_contains(output, "Brain default constructor");
}
