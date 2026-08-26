#include "items/Item.h"

#include <iostream>

// ==========================================
// Constructor
// ==========================================

Item::Item(
    const std::string& name,
    const std::string& description,
    int price
)
    : name(name),
      description(description),
      price(price)
{
}

// ==========================================
// Destructor
// ==========================================

Item::~Item()
{
}

// ==========================================
// Get Name
// ==========================================

const std::string& Item::getName() const
{
    return name;
}

// ==========================================
// Get Description
// ==========================================

const std::string& Item::getDescription() const
{
    return description;
}

// ==========================================
// Get Price
// ==========================================

int Item::getPrice() const
{
    return price;
}

// ==========================================
// Use Item
// ==========================================

void Item::use(Character& target)
{
    // Item cơ bản không có hiệu ứng sử dụng.
    // Các class con như Potion / Weapon / Armor
    // sẽ override hàm này.
}

// ==========================================
// Show Info
// ==========================================

void Item::showInfo() const
{
    std::cout << "Name        : " << name << '\n';
    std::cout << "Description : " << description << '\n';
    std::cout << "Price       : " << price << '\n';
}