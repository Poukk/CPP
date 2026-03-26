#include <iostream>

#include "Contact.hpp"

Contact::Contact() {}

Contact::Contact(const Contact &other) { *this = other; }

Contact::~Contact() {}

Contact &Contact::operator=(const Contact &other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        nickname = other.nickname;
        phoneNumber = other.phoneNumber;
        darkestSecret = other.darkestSecret;
    }
    return *this;
}

void Contact::setFirstName(const std::string &value) { firstName = value; }
void Contact::setLastName(const std::string &value) { lastName = value; }
void Contact::setNickname(const std::string &value) { nickname = value; }
void Contact::setPhoneNumber(const std::string &value) { phoneNumber = value; }
void Contact::setDarkestSecret(const std::string &value) { darkestSecret = value; }

const std::string &Contact::getFirstName() const { return firstName; }
const std::string &Contact::getLastName() const { return lastName; }
const std::string &Contact::getNickname() const { return nickname; }
const std::string &Contact::getPhoneNumber() const { return phoneNumber; }
const std::string &Contact::getDarkestSecret() const { return darkestSecret; }

void Contact::display() const {
    std::cout << "First name: " << firstName << std::endl;
    std::cout << "Last name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone number: " << phoneNumber << std::endl;
    std::cout << "Darkest secret: " << darkestSecret << std::endl;
}
