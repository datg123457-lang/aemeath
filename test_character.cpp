#include "entities/Warrior.h"
#include <iostream>

int main()
{
    Warrior warrior(1, "Arthas");

    std::cout << "Class: " << warrior.getClassName() << '\n';
    std::cout << "Name: " << warrior.getName() << '\n';
    std::cout << "Level: " << warrior.getLevel() << '\n';

    std::cout << "HP: "
              << warrior.getHP()
              << "/"
              << warrior.getMaxHP()
              << '\n';

    std::cout << "Attack: "
              << warrior.getAttack()
              << '\n';

    std::cout << "Defense: "
              << warrior.getDefense()
              << '\n';

    std::cout << "Intelligence: "
              << warrior.getIntelligence()
              << '\n';

    std::cout << "Agility: "
              << warrior.getAgility()
              << '\n';

    return 0;
}