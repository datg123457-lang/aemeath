#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

enum class AreaType
{
    DARK_FOREST,
    ANCIENT_RUINS,
    FROZEN_PEAK,
    SHADOW_CASTLE,
    DEMON_REALM
};

struct Area
{
    int id;
    std::string name;
    AreaType type;
};

class Map
{
private:
    std::vector<Area> areas;

public:
    Map();

    const std::vector<Area>& getAreas() const;

    const Area* getArea(int id) const;

    void showMap() const;
};

#endif