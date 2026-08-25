#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include "items/Item.h"

#include <vector>

class Character;

class InventorySystem
{
private:
    // Danh sách vật phẩm
    std::vector<Item*> items;

    // Số ô tối đa
    int maxSlots;

private:
    // Kiểm tra vị trí có hợp lệ không
    bool isValidIndex(int index) const;

public:
    // ==========================================
    // Constructor / Destructor
    // ==========================================

    explicit InventorySystem(int maxSlots = 20);

    ~InventorySystem();

    // Không cho phép copy
    InventorySystem(const InventorySystem&) = delete;
    InventorySystem& operator=(const InventorySystem&) = delete;

    // ==========================================
    // Item Management
    // ==========================================

    bool addItem(Item* item);

    bool removeItem(int index);

    // ==========================================
    // Inventory
    // ==========================================

    void showInventory() const;

    void clearInventory();

    int getItemCount() const;

    int getMaxSlots() const;

    bool isFull() const;

    bool isEmpty() const;

    // ==========================================
    // Item Usage
    // ==========================================

    bool useItem(
        int index,
        Character& target
    );

    // ==========================================
    // Getter
    // ==========================================

    Item* getItem(int index) const;

    const std::vector<Item*>& getItems() const;
};

#endif