#ifndef SKILL_H
#define SKILL_H

#include <string>

class Character;

class Skill
{
protected:
    std::string name;
    std::string description;
    int manaCost;
    int basePower;

public:
    Skill(
        const std::string& name,
        const std::string& description,
        int manaCost,
        int basePower
    );

    virtual ~Skill();

    const std::string& getName() const;
    const std::string& getDescription() const;
    int getManaCost() const;
    int getBasePower() const;

    virtual int calculateDamage(const Character& caster) const = 0;
    virtual void execute(Character& caster, Character& target);
    virtual std::string getSkillType() const = 0;
};

#endif