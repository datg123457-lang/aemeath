#include "entities/Entity.h"

Entity::Entity(int id)
    : id(id)
{
}

Entity::~Entity() = default;

int Entity::getId() const
{
    return id;
}