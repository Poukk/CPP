#include "PhoneBook.hpp"

#include <cctype>
#include <iostream>
#include <string>

static std::string trimWhitespace(const std::string &value) {
    std::string::size_type start;
    std::string::size_type end;

    start = 0;
    while (start < value.length() &&
           std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }
    end = value.length();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }
    return value.substr(start, end - start);
}

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command)) {
            break;
        }
        command = trimWhitespace(command);
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
