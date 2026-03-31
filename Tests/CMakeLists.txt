cmake_minimum_required(VERSION 3.20)

project(CPPTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(FetchContent)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(TestHarness)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

set(MODULE00_EX00_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 00/ex00")
set(MODULE00_EX01_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 00/ex01")
set(MODULE01_EX00_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 01/ex00")
set(MODULE01_EX01_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 01/ex01")
set(MODULE01_EX02_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 01/ex02")
set(MODULE01_EX03_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 01/ex03")
set(MODULE01_EX04_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 01/ex04")
set(MODULE01_EX05_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Module 01/ex05")

add_cpp_exercise_app(module00_ex00_app "${MODULE00_EX00_DIR}"
  megaphone.cpp
)

add_cpp_exercise_library(module00_ex01_lib "${MODULE00_EX01_DIR}"
  Contact.cpp
  PhoneBook.cpp
)

add_cpp_exercise_app(module00_ex01_app "${MODULE00_EX01_DIR}"
  main.cpp
  Contact.cpp
  PhoneBook.cpp
)

add_cpp_exercise_library(module01_ex00_lib "${MODULE01_EX00_DIR}"
  Zombie.cpp
  newZombie.cpp
  randomChump.cpp
)

add_cpp_exercise_app(module01_ex00_app "${MODULE01_EX00_DIR}"
  main.cpp
  Zombie.cpp
  newZombie.cpp
  randomChump.cpp
)

add_cpp_exercise_library(module01_ex01_lib "${MODULE01_EX01_DIR}"
  Zombie.cpp
  zombieHorde.cpp
)

add_cpp_exercise_app(module01_ex01_app "${MODULE01_EX01_DIR}"
  main.cpp
  Zombie.cpp
  zombieHorde.cpp
)

add_cpp_exercise_app(module01_ex02_app "${MODULE01_EX02_DIR}"
  main.cpp
)

add_cpp_exercise_library(module01_ex03_lib "${MODULE01_EX03_DIR}"
  Weapon.cpp
  HumanA.cpp
  HumanB.cpp
)

add_cpp_exercise_app(module01_ex03_app "${MODULE01_EX03_DIR}"
  main.cpp
  Weapon.cpp
  HumanA.cpp
  HumanB.cpp
)

add_cpp_exercise_library(module01_ex04_lib "${MODULE01_EX04_DIR}"
  FileReplacer.cpp
)

add_cpp_exercise_app(module01_ex04_app "${MODULE01_EX04_DIR}"
  main.cpp
  FileReplacer.cpp
)

add_cpp_exercise_library(module01_ex05_lib "${MODULE01_EX05_DIR}"
  Harl.cpp
)

add_cpp_exercise_app(module01_ex05_app "${MODULE01_EX05_DIR}"
  main.cpp
  Harl.cpp
)

add_cpp_gtest_binary(module00_unit_tests
  SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/support/stream_redirect.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module00_ex01_contact_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module00_ex01_phonebook_storage_test.cpp"
  LIBRARIES
    module00_ex01_lib
  INCLUDE_DIRS
    "${MODULE00_EX01_DIR}"
)

add_cpp_gtest_binary(module00_integration_tests
  SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/support/fixture_loader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/support/process_runner.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module00_ex00_megaphone_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module00_ex01_phonebook_cli_test.cpp"
  COMPILE_DEFINITIONS
    MODULE00_EX00_APP_PATH="$<TARGET_FILE:module00_ex00_app>"
    MODULE00_EX01_APP_PATH="$<TARGET_FILE:module00_ex01_app>"
    TESTS_FIXTURES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/fixtures"
)

add_cpp_gtest_binary(module01_ex00_unit_tests
  SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/support/stream_redirect.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module01_ex00_zombie_test.cpp"
  LIBRARIES
    module01_ex00_lib
  INCLUDE_DIRS
    "${MODULE01_EX00_DIR}"
)

add_cpp_gtest_binary(module01_ex01_unit_tests
  SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/support/stream_redirect.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module01_ex01_zombie_horde_test.cpp"
  LIBRARIES
    module01_ex01_lib
  INCLUDE_DIRS
    "${MODULE01_EX01_DIR}"
)

add_cpp_gtest_binary(module01_unit_tests
  SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/support/stream_redirect.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/support/temp_dir.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module01_ex03_weapon_human_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module01_ex04_file_replacer_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/module01_ex05_harl_test.cpp"
  LIBRARIES
    module01_ex03_lib
    module01_ex04_lib
    module01_ex05_lib
  INCLUDE_DIRS
    "${MODULE01_EX03_DIR}"
    "${MODULE01_EX04_DIR}"
    "${MODULE01_EX05_DIR}"
)

add_cpp_gtest_binary(module01_integration_tests
  SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/support/process_runner.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/support/temp_dir.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module01_ex00_zombie_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module01_ex01_zombie_horde_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module01_ex02_brain_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module01_ex03_violence_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module01_ex04_replace_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/integration/module01_ex05_harl_test.cpp"
  INCLUDE_DIRS
    "${MODULE01_EX05_DIR}"
  COMPILE_DEFINITIONS
    MODULE01_EX00_APP_PATH="$<TARGET_FILE:module01_ex00_app>"
    MODULE01_EX01_APP_PATH="$<TARGET_FILE:module01_ex01_app>"
    MODULE01_EX02_APP_PATH="$<TARGET_FILE:module01_ex02_app>"
    MODULE01_EX03_APP_PATH="$<TARGET_FILE:module01_ex03_app>"
    MODULE01_EX04_APP_PATH="$<TARGET_FILE:module01_ex04_app>"
    MODULE01_EX05_APP_PATH="$<TARGET_FILE:module01_ex05_app>"
)
