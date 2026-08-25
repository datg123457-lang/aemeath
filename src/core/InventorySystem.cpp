#include "core/InventorySystem.h"

#include "entities/Character.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

InventorySystem::InventorySystem(int maxSlots)
    : maxSlots(maxSlots)
{
    if (this->maxSlots < 1)
    {
        this->maxSlots = 1;
    }
}

// ==========================================
// Destructor
// ==========================================

InventorySystem::~InventorySystem()
{
    clearInventory();
}

// ==========================================
// Kiểm tra Index
// ==========================================

bool InventorySystem::isValidIndex(int index) const
{
    return index >= 0 &&
           index < static_cast<int>(items.size());
}

// ==========================================
// Add Item
// ==========================================

bool InventorySystem::addItem(Item* item)
{
    if (item == nullptr)
    {
        return false;
    }

    if (isFull())
    {
        cout << "Inventory is full!\n";

        return false;
    }

    items.push_back(item);

    cout << "Added item: "
         << item->getName()
         << "\n";

    return true;
}

// ==========================================
// Remove Item
// ==========================================

bool InventorySystem::removeItem(int index)
{
    if (!isValidIndex(index))
    {
        cout << "Invalid item index!\n";

        return false;
    }

    Item* item = items[index];

    cout << "Removed item: "
         << item->getName()
         << "\n";

    delete item;

    items.erase(
        items.begin() + index
    );

    return true;
}

// ==========================================
// Show Inventory
// ==========================================

void InventorySystem::showInventory() const
{
    cout << "\n";
    cout << "=====================================\n";
    cout << "             INVENTORY\n";
    cout << "=====================================\n";

    cout << "Slots: "
         << items.size()
         << "/"
         << maxSlots
         << "\n";

    cout << "-------------------------------------\n";

    if (items.empty())
    {
        cout << "Inventory is empty.\n";

        cout << "=====================================\n";

        return;
    }

    for (size_t i = 0; i < items.size(); ++i)
    {
        cout << "\n";
        cout << "[" << i + 1 << "]\n";

        if (items[i] != nullptr)
        {
            items[i]->showInfo();
        }
    }

    cout << "\n";
    cout << "=====================================\n";
}

// ==========================================
// Clear Inventory
// ==========================================

void InventorySystem::clearInventory()
{
    for (Item* item : items)
    {
        delete item;
    }

    items.clear();
}

// ==========================================
// Get Item Count
// ==========================================

int InventorySystem::getItemCount() const
{
    return static_cast<int>(items.size());
}

// ==========================================
// Get Max Slots
// ==========================================

int InventorySystem::getMaxSlots() const
{
    return maxSlots;
}

// ==========================================
// Is Full
// ==========================================

bool InventorySystem::isFull() const
{
    return static_cast<int>(items.size()) >= maxSlots;
}

// ==========================================
// Is Empty
// ==========================================

bool InventorySystem::isEmpty() const
{
    return items.empty();
}

// ==========================================
// Use Item
// ==========================================

bool InventorySystem::useItem(
    int index,
    Character& target
)
{
    if (!isValidIndex(index))
    {
        cout << "Invalid item index!\n";

        return false;
    }

    Item* item = items[index];

    if (item == nullptr)
    {
        return false;
    }

    cout << "\nUsing: "
         << item->getName()
         << "\n";

    // Gọi hàm use() của Item
    item->use(target);

    return true;
}

// ==========================================
// Get Item
// ==========================================

Item* InventorySystem::getItem(int index) const
{
    if (!isValidIndex(index))
    {
        return nullptr;
    }

    return items[index];
}

// ==========================================
// Get All Items
// ==========================================

const vector<Item*>& InventorySystem::getItems() const
{
    return items;
}