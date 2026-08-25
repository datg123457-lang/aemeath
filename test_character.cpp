#include "entities/Warrior.h"
#include "entities/Mage.h"
#include "entities/Archer.h"
#include <iostream>

int main()
{
    Warrior warrior(1, "Arthas");
    Mage mage(2, "Jaina");
    Archer archer(3, "Legolas");

    std::cout << warrior.getClassName()
              << " - Damage: "
              << warrior.calculateAttackDamage()
              << '\n';

    std::cout << mage.getClassName()
              << " - Damage: "
              << mage.calculateAttackDamage()
              << '\n';

    std::cout << archer.getClassName()
              << " - Damage: "
              << archer.calculateAttackDamage()
              << '\n';

    return 0;
}