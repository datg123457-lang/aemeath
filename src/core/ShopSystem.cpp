#include "core/ShopSystem.h"
#include "items/Armor.h"
#include "items/Potion.h"
#include "items/Weapon.h"
#include "entities/Character.h"
 
#include <iostream>
 
// ==========================================
// Constructor - seed vai vat pham mau ban dau
// ==========================================
 
ShopSystem::ShopSystem()
{
    catalog.push_back(new Potion("Binh Mau Nho", "Hoi 30 HP", 20, 30, "HP"));
    catalog.push_back(new Potion("Binh Mau Lon", "Hoi 80 HP", 50, 80, "HP"));
    catalog.push_back(new Weapon("Kiem Go", "Vu khi co ban", 30, 5, "Kiem"));
    catalog.push_back(new Weapon("Kiem Sat", "Vu khi manh hon", 100, 15, "Kiem"));
    catalog.push_back(new Armor("Ao Da", "Giap nhe", 40, 5, "Nhe"));
    catalog.push_back(new Armor("Giap Sat", "Giap nang, phong thu cao", 120, 15, "Nang"));
}
 
// ==========================================
// Destructor - don dep cac vat pham mau
// ==========================================
 
ShopSystem::~ShopSystem()
{
    for (Item* item : catalog)
    {
        delete item;
    }
    catalog.clear();
}
 
// ==========================================
// Clone Item theo dung kieu that su
// ==========================================
 
Item* ShopSystem::cloneItem(const Item* prototype) const
{
    if (const Armor* armor = dynamic_cast<const Armor*>(prototype))
    {
        return new Armor(
            armor->getName(),
            armor->getDescription(),
            armor->getPrice(),
            armor->getDefenseBonus(),
            armor->getArmorType()
        );
    }
 
    if (const Potion* potion = dynamic_cast<const Potion*>(prototype))
    {
        return new Potion(
            potion->getName(),
            potion->getDescription(),
            potion->getPrice(),
            potion->getRestoreAmount(),
            potion->getPotionType()
        );
    }
 
    if (const Weapon* weapon = dynamic_cast<const Weapon*>(prototype))
    {
        return new Weapon(
            weapon->getName(),
            weapon->getDescription(),
            weapon->getPrice(),
            weapon->getDamage(),
            weapon->getWeaponType()
        );
    }
 
    // Khong nhan dien duoc kieu -> khong the clone an toan
    return nullptr;
}
 
// ==========================================
// Them vat pham vao catalog
// ==========================================
 
void ShopSystem::addToCatalog(Item* item)
{
    if (item != nullptr)
    {
        catalog.push_back(item);
    }
}
 
// ==========================================
// Hien danh sach vat pham dang ban
// ==========================================
 
void ShopSystem::showCatalog() const
{
    std::cout << "===== CUA HANG =====\n";
    for (size_t i = 0; i < catalog.size(); ++i)
    {
        std::cout << i + 1 << ". " << catalog[i]->getName()
                   << " - Gia: " << catalog[i]->getPrice()
                   << " - " << catalog[i]->getDescription() << '\n';
    }
    std::cout << "0. Roi khoi shop\n";
}
 
// ==========================================
// Mua vat pham
// ==========================================
 
bool ShopSystem::buyItem(Character& player, int index)
{
    if (index < 0 || index >= static_cast<int>(catalog.size()))
    {
        std::cout << "Lua chon khong hop le.\n";
        return false;
    }
 
    Item* prototype = catalog[index];
 
    if (player.getGold() < prototype->getPrice())
    {
        std::cout << "Ban khong du tien de mua " << prototype->getName() << ".\n";
        return false;
    }
 
    Item* newItem = cloneItem(prototype);
    if (newItem == nullptr)
    {
        std::cout << "Khong the tao vat pham nay.\n";
        return false;
    }
 
    if (!player.getInventory().addItem(newItem))
    {
        std::cout << "Tui do da day, khong the mua them.\n";
        delete newItem;
        return false;
    }
 
    player.setGold(player.getGold() - prototype->getPrice());
    std::cout << "Ban da mua " << newItem->getName() << " thanh cong!\n";
    return true;
}
 
// ==========================================
// Mo giao dien shop
// ==========================================
 
void ShopSystem::openShop(Character& player)
{
    int choice = -1;
 
    while (choice != 0)
    {
        showCatalog();
        std::cout << "So du: " << player.getGold() << " vang\n";
        std::cout << "Chon vat pham muon mua (0 de thoat): ";
        std::cin >> choice;
 
        if (choice > 0)
        {
            buyItem(player, choice - 1);
        }
    }
}