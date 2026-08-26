#include "core/Skill.h"
#include "entities/Character.h"
 
#include <iostream>
 
// ==========================================
// Constructor
// ==========================================
 
Skill::Skill(
    const std::string& name,
    const std::string& description,
    int manaCost,
    int basePower
)
    : name(name),
      description(description),
      manaCost(manaCost),
      basePower(basePower)
{
}
 
// ==========================================
// Destructor
// ==========================================
 
Skill::~Skill()
{
}
 
// ==========================================
// Getters
// ==========================================
 
const std::string& Skill::getName() const
{
    return name;
}
 
const std::string& Skill::getDescription() const
{
    return description;
}
 
int Skill::getManaCost() const
{
    return manaCost;
}
 
int Skill::getBasePower() const
{
    return basePower;
}
 
// ==========================================
// Execute (thuc thi ky nang len muc tieu)
// calculateDamage() la pure virtual, se do lop con
// (VD: FireSkill, IceSkill...) tu dinh nghia
// ==========================================
 
void Skill::execute(Character& caster, Character& target)
{
    // Luu y: Character hien chua co chi so MP,
    // nen chua the tru manaCost o day. Can bo sung MP
    // vao Character truoc khi kich hoat logic tru mana.
 
    int damage = calculateDamage(caster);
    target.takeDamage(damage);
 
    std::cout << caster.getName() << " da dung ky nang " << name
               << ", gay " << damage << " sat thuong len " << target.getName() << "!\n";
}
