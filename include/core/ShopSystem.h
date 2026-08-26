#ifndef SHOPSYSTEM_H
#define SHOPSYSTEM_H
 
#include "items/Item.h"
 
#include <vector>
 
class Character; // Forward declaration
 
class ShopSystem
{
private:
    // Cac vat pham "mau" dang ban trong shop.
    // Khi nguoi choi mua, shop se tao 1 ban sao (clone) de dua vao tui do,
    // con vat pham mau trong catalog van giu nguyen de ban tiep cho nguoi khac.
    std::vector<Item*> catalog;
 
    // Tao ban sao cua 1 vat pham dua vao kieu that su cua no (Armor/Potion/Weapon)
    Item* cloneItem(const Item* prototype) const;
 
public:
    ShopSystem();
    ~ShopSystem();
 
    // Khong cho phep copy (dang quan ly con tro dong)
    ShopSystem(const ShopSystem&) = delete;
    ShopSystem& operator=(const ShopSystem&) = delete;
 
    // Them 1 vat pham mau vao catalog (ShopSystem se quan ly vong doi cua no)
    void addToCatalog(Item* item);
 
    // Hien danh sach vat pham dang ban
    void showCatalog() const;
 
    // Mua vat pham theo chi so trong catalog
    // Tra ve true neu mua thanh cong (du tien + con cho trong tui do)
    bool buyItem(Character& player, int index);
 
    // Mo giao dien shop (vong lap nhap lieu console)
    void openShop(Character& player);
};
 
#endif // SHOPSYSTEM_H