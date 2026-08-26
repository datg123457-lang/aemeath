#include "items/Potion.h"
#include "entities/Character.h"
 
#include <iostream>
#include <algorithm>
 
// ==========================================
// Constructor
// ==========================================
 
Potion::Potion(
    const std::string& name,
    const std::string& description,
    int price,
    int restoreAmount,
    const std::string& potionType
)
    : Item(name, description, price),
      restoreAmount(restoreAmount),
      potionType(potionType)
{
}
 
// ==========================================
// Destructor
// ==========================================
 
Potion::~Potion()
{
}
 
// ==========================================
// Get Restore Amount
// ==========================================
 
int Potion::getRestoreAmount() const
{
    return restoreAmount;
}
 
// ==========================================
// Get Potion Type
// ==========================================
 
const std::string& Potion::getPotionType() const
{
    return potionType;
}
 
// ==========================================
// Use (Uong thuoc)
// ==========================================
 
void Potion::use(Character& target)
{
    if (potionType == "HP")
    {
        int newHP = std::min(target.getHP() + restoreAmount, target.getMaxHP());
        target.setHP(newHP);
        std::cout << target.getName() << " da hoi phuc " << restoreAmount << " HP.\n";
    }
    else if (potionType == "MP")
    {
        // Nhan vat hien chua co chi so MP trong Character,
        // can bo sung MP vao Character truoc khi dung binh nay.
        std::cout << target.getName() << " chua ho tro he thong MP.\n";
    }
    else
    {
        std::cout << "Loai binh thuoc khong xac dinh.\n";
    }
}
 
// ==========================================
// Show Info
// ==========================================
 
void Potion::showInfo() const
{
    Item::showInfo();
    std::cout << "Loai thuoc   : " << potionType << '\n';
    std::cout << "Hoi phuc     : +" << restoreAmount << '\n';
}
