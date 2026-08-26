#include "items/Armor.h"
#include "entities/Character.h"
 
#include <iostream>
 
// ==========================================
// Constructor
// ==========================================
 
Armor::Armor(
    const std::string& name,
    const std::string& description,
    int price,
    int defenseBonus,
    const std::string& armorType
)
    : Item(name, description, price),
      defenseBonus(defenseBonus),
      armorType(armorType)
{
}
 
// ==========================================
// Destructor
// ==========================================
 
Armor::~Armor()
{
}
 
// ==========================================
// Get Defense Bonus
// ==========================================
 
int Armor::getDefenseBonus() const
{
    return defenseBonus;
}
 
// ==========================================
// Get Armor Type
// ==========================================
 
const std::string& Armor::getArmorType() const
{
    return armorType;
}
 
// ==========================================
// Use (Trang bi giap)
// ==========================================
 
void Armor::use(Character& target)
{
    target.setDefense(target.getDefense() + defenseBonus);
    std::cout << target.getName() << " da trang bi " << name
               << ", tang " << defenseBonus << " diem phong thu.\n";
}
 
// ==========================================
// Show Info
// ==========================================
 
void Armor::showInfo() const
{
    Item::showInfo();
    std::cout << "Loai giap    : " << armorType << '\n';
    std::cout << "Phong thu    : +" << defenseBonus << '\n';
}