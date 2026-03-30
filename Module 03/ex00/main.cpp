#include "ClapTrap.hpp"

int main(void) {
    ClapTrap alpha("Alpha");
    ClapTrap beta("Beta");
    ClapTrap gamma(alpha);
    ClapTrap delta;

    delta = beta;

    alpha.attack("target dummy");
    alpha.takeDamage(3);
    alpha.beRepaired(2);

    beta.takeDamage(10);
    beta.attack("Alpha");
    beta.beRepaired(1);

    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.attack("practice bot");
    gamma.beRepaired(1);

    return (0);
}
