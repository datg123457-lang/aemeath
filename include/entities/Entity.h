#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
    int id;

public:
    Entity(int id);
    virtual ~Entity();

    int getId() const;
};

#endif