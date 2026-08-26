#ifndef CHARACTER_H
#define CHARACTER_H
 
#include "Entity.h"
#include "core/InventorySystem.h"
#include <string>
 
class Character : public Entity
{
protected:
    std::string name;
 
    int level;
    int experience;
    int gold;
 
    int maxHP;
    int hp;
 
    int attack;
    int defense;
    int intelligence;
    int agility;
 
    // Tui do rieng cua nhan vat (moi Character tu quan ly tui do)
    InventorySystem* inventory;
 
public:
    Character(
        int id,
        const std::string& name,
        int maxHP,
        int attack,
        int defense,
        int intelligence,
        int agility,
        int inventorySlots = 20 // Tham so moi, co gia tri mac dinh nen khong pha vo code cu
    );
 
    virtual ~Character();
 
    // Khong cho phep copy vi InventorySystem ben trong khong cho copy
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;
 
    const std::string& getName() const;
 
    int getLevel() const;
    int getExperience() const;
    int getGold() const;
 
    int getHP() const;
    int getMaxHP() const;
 
    int getAttack() const;
    int getDefense() const;
    int getIntelligence() const;
    int getAgility() const;
 
    void setHP(int hp);
    void setGold(int gold);
 
    // Setter moi them - can thiet de Weapon/Armor co the thay doi chi so khi trang bi
    void setAttack(int attack);
    void setDefense(int defense);
 
    // Truy cap tui do cua nhan vat
    InventorySystem& getInventory() const;
 
    virtual int calculateAttackDamage() const;
    virtual void takeDamage(int damage);
    virtual bool isAlive() const;
 
    virtual void gainExperience(int amount);
    virtual void levelUp();
 
    virtual void attackTarget(Character& target);
 
    virtual std::string getClassName() const = 0;
};
 
#endif
