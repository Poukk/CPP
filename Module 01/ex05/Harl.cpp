#include "Harl.hpp"
#include <iostream>

Harl::Harl() {}

Harl::~Harl() {}

void Harl::debug(void) { std::cout << HARL_DEBUG << std::endl; }

void Harl::info(void) { std::cout << HARL_INFO << std::endl; }

void Harl::warning(void) { std::cout << HARL_WARNING << std::endl; }

void Harl::error(void) { std::cout << HARL_ERROR << std::endl; }

void Harl::complain(std::string level) {
    const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    HarlAction actions[4] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
    int index;

    index = 0;
    while (index < 4) {
        if (levels[index] == level) {
            (this->*actions[index])();
            return;
        }
        index++;
    }
    std::cout << "[UNKNOWN LOG LEVEL]" << std::endl;
}
