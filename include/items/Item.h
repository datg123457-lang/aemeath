#ifndef ITEM_H
#define ITEM_H

#include <string>

class Character;

class Item
{
protected:
    std::string name;
    std::string description;
    int price;

public:
    Item(
        const std::string& name,
        const std::string& description,
        int price
    );

    virtual ~Item();

    const std::string& getName() const;
    const std::string& getDescription() const;
    int getPrice() const;

    virtual void use(Character& target);
    virtual void showInfo() const;
};

#endif