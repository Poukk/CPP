#include "PhoneBook.hpp"

#include <iostream>
#include <string>

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command)) {
            break;
        }
        if (command == "ADD") {
            if (!phoneBook.addContact()) {
                break;
            }
        } else if (command == "SEARCH") {
            if (!phoneBook.searchContact()) {
                break;
            }
        } else if (command == "EXIT") {
            break;
        }
    }
    return 0;
}
