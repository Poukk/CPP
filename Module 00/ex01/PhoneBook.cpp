#include "PhoneBook.hpp"

#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

PhoneBook::PhoneBook() : nextIndex(0), contactCount(0) {}

PhoneBook::PhoneBook(const PhoneBook &other) { *this = other; }

PhoneBook::~PhoneBook() {}

PhoneBook &PhoneBook::operator=(const PhoneBook &other) {
    int i;

    if (this != &other) {
        nextIndex = other.nextIndex;
        contactCount = other.contactCount;
        for (i = 0; i < maxContacts; ++i) {
            contacts[i] = other.contacts[i];
        }
    }
    return *this;
}

static void printCell(const std::string &value) {
    if (value.length() <= 10) {
        std::cout << std::setw(10) << value;
        return;
    }
    std::cout << std::setw(10) << (value.substr(0, 9) + ".");
}

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

static bool readNonEmptyField(const std::string &prompt, std::string &value) {
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            return false;
        }
        if (!value.empty()) {
            return true;
        }
        std::cout << "Field cannot be empty." << std::endl;
    }
}

bool PhoneBook::addContact() {
    Contact contact;
    std::string input;

    if (!readNonEmptyField("First name: ", input)) {
        return false;
    }
    contact.setFirstName(input);
    if (!readNonEmptyField("Last name: ", input)) {
        return false;
    }
    contact.setLastName(input);
    if (!readNonEmptyField("Nickname: ", input)) {
        return false;
    }
    contact.setNickname(input);
    if (!readNonEmptyField("Phone number: ", input)) {
        return false;
    }
    contact.setPhoneNumber(input);
    if (!readNonEmptyField("Darkest secret: ", input)) {
        return false;
    }
    contact.setDarkestSecret(input);

    contacts[nextIndex] = contact;
    nextIndex = (nextIndex + 1) % maxContacts;
    if (contactCount < maxContacts) {
        contactCount++;
    }
    return true;
}

bool PhoneBook::searchContact() const {
    std::string input;
    std::string indexString;
    int index;
    const Contact *contact;
    int i;
    std::string::size_type j;

    if (contactCount == 0) {
        std::cout << "PhoneBook is empty." << std::endl;
        return true;
    }
    printCell("Index");
    std::cout << "|";
    printCell("First name");
    std::cout << "|";
    printCell("Last name");
    std::cout << "|";
    printCell("Nickname");
    std::cout << std::endl;
    for (i = 0; i < contactCount; ++i) {
        contact = getContact(i);
        indexString = static_cast<char>('0' + i);
        printCell(indexString);
        std::cout << "|";
        printCell(contact->getFirstName());
        std::cout << "|";
        printCell(contact->getLastName());
        std::cout << "|";
        printCell(contact->getNickname());
        std::cout << std::endl;
    }
    std::cout << "Index: ";
    if (!std::getline(std::cin, input)) {
        return false;
    }
    input = trimWhitespace(input);
    index = -1;
    if (!input.empty()) {
        index = std::atoi(input.c_str());
        for (j = 0; j < input.length(); ++j) {
            if (input[j] < '0' || input[j] > '9') {
                index = -1;
                break;
            }
        }
    }
    contact = getContact(index);
    if (contact == 0) {
        std::cout << "Invalid index." << std::endl;
        return true;
    }
    contact->display();
    return true;
}

const Contact *PhoneBook::getContact(int index) const {
    int physicalIndex;

    if (index < 0 || index >= contactCount) {
        return 0;
    }
    if (contactCount < maxContacts) {
        physicalIndex = index;
    } else {
        physicalIndex = (nextIndex + index) % maxContacts;
    }
    return &contacts[physicalIndex];
}

int PhoneBook::getContactCount() const { return contactCount; }

int PhoneBook::getMaxContacts() const { return maxContacts; }
