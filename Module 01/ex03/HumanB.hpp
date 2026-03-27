#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB {
  private:
    std::string name;
    Weapon *weapon;

  public:
    HumanB(const std::string &name);
    ~HumanB();

    void setWeapon(Weapon &newWeapon);
    void attack() const;
};

#endif
