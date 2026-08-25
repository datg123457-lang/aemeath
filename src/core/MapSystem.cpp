#include "core/MapSystem.h"

#include <iostream>

Map::Map()
{
    areas =
    {
        {
            1,
            "Dark Forest",
            AreaType::DARK_FOREST
        },

        {
            2,
            "Ancient Ruins",
            AreaType::ANCIENT_RUINS
        },

        {
            3,
            "Frozen Peak",
            AreaType::FROZEN_PEAK
        },

        {
            4,
            "Shadow Castle",
            AreaType::SHADOW_CASTLE
        },

        {
            5,
            "Demon Realm",
            AreaType::DEMON_REALM
        }
    };
}

const std::vector<Area>& Map::getAreas() const
{
    return areas;
}

const Area* Map::getArea(int id) const
{
    for (const Area& area : areas)
    {
        if (area.id == id)
        {
            return &area;
        }
    }

    return nullptr;
}

void Map::showMap() const
{
    std::cout << "\n";
    std::cout << "=====================================\n";
    std::cout << "              WORLD MAP\n";
    std::cout << "=====================================\n";

    for (const Area& area : areas)
    {
        std::cout
            << area.id
            << ". "
            << area.name
            << "\n";
    }

    std::cout << "=====================================\n";
}