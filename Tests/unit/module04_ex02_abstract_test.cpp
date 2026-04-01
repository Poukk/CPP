#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "support/process_runner.hpp"
#include "support/stream_redirect.hpp"
#include "support/temp_dir.hpp"

namespace {

void expect_contains(const std::string &haystack, const std::string &needle) {
    EXPECT_NE(haystack.find(needle), std::string::npos);
}

std::string shell_quote(const std::string &value) {
    return "'" + value + "'";
}

}  // namespace

TEST(Module04Ex02AbstractUnitTest, AnimalIsAbstractAndKeepsVirtualDestruction) {
    EXPECT_TRUE((std::is_abstract<Animal>::value));
    EXPECT_TRUE((std::is_base_of<Animal, Dog>::value));
    EXPECT_TRUE((std::is_base_of<Animal, Cat>::value));
    EXPECT_TRUE((std::has_virtual_destructor<Animal>::value));
}

TEST(Module04Ex02AbstractUnitTest, DogCopyAndCatAssignmentRemainDeep) {
    Dog dog;
    dog.setIdea(0, "Guard the yard");
    Dog dog_copy(dog);
    dog.setIdea(0, "Sleep on the porch");

    Cat cat_source;
    Cat cat_copy;
    cat_source.setIdea(0, "Climb the curtains");
    cat_copy = cat_source;
    cat_source.setIdea(0, "Take a nap");

    EXPECT_NE(dog.getBrain(), dog_copy.getBrain());
    EXPECT_EQ(dog_copy.getIdea(0), "Guard the yard");
    EXPECT_NE(cat_source.getBrain(), cat_copy.getBrain());
    EXPECT_EQ(cat_copy.getIdea(0), "Climb the curtains");
}

TEST(Module04Ex02AbstractUnitTest, AnimalsCanStillBeDeletedThroughBasePointers) {
    test_support::scoped_output_capture capture(std::cout);
    Animal *animals[2] = {new Dog(), new Cat()};

    animals[0]->makeSound();
    animals[1]->makeSound();
    delete animals[0];
    delete animals[1];

    const std::string output = capture.str();
    expect_contains(output, "Woof woof!");
    expect_contains(output, "Meow meow!");
    expect_contains(output, "Dog destructor called");
    expect_contains(output, "Cat destructor called");
    expect_contains(output, "Animal destructor");
}

TEST(Module04Ex02AbstractUnitTest, InstantiatingAnimalFailsToCompile) {
    test_support::scoped_temp_dir temp_dir;
    const std::string source_path = temp_dir.file_path("instantiate_animal.cpp");
    const std::string object_path = temp_dir.file_path("instantiate_animal.o");
    const std::string source =
        "#include \"Animal.hpp\"\n"
        "int main() {\n"
        "    Animal test;\n"
        "    return 0;\n"
        "}\n";
    const std::string command =
        "c++ -std=c++98 -Wall -Wextra -Werror -I" + shell_quote(MODULE04_EX02_DIR) +
        " -c " + shell_quote(source_path) +
        " -o " + shell_quote(object_path);

    temp_dir.write_file("instantiate_animal.cpp", source);
    const test_support::ProcessResult result =
        test_support::run_process("/bin/sh", std::vector<std::string>{"-c", command});

    EXPECT_NE(result.exit_code, 0);
    expect_contains(result.stderr_output, "Animal");
    expect_contains(result.stderr_output, "abstract");
}
