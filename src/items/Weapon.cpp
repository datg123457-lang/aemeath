#include "items/Weapon.h"
#include "entities/Character.h"
 
#include <iostream>
 
// ==========================================
// Constructor
// ==========================================
 
Weapon::Weapon(
    const std::string& name,
    const std::string& description,
    int price,
    int damage,
    const std::string& weaponType
)
    : Item(name, description, price),
      damage(damage),
      weaponType(weaponType)
{
}
 
// ==========================================
// Destructor
// ==========================================
 
Weapon::~Weapon()
{
}
 
// ==========================================
// Get Damage
// ==========================================
 
int Weapon::getDamage() const
{
    return damage;
}
 
// ==========================================
// Get Weapon Type
// ==========================================
 
const std::string& Weapon::getWeaponType() const
{
    return weaponType;
}
 
// ==========================================
// Use (Trang bi vu khi)
// ==========================================
 
void Weapon::use(Character& target)
{
    target.setAttack(target.getAttack() + damage);
    std::cout << target.getName() << " da trang bi " << name
               << ", tang " << damage << " diem tan cong.\n";
}
 
// ==========================================
// Show Info
// ==========================================
 
void Weapon::showInfo() const
{
    Item::showInfo();
    std::cout << "Loai vu khi  : " << weaponType << '\n';
    std::cout << "Sat thuong   : +" << damage << '\n';
}