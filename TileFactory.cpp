//
// Created by leonardo on 19/08/20.
//
#include "Tile.h"
#include "TileFactory.h"

#include <utility>


Tile *TileFactory::createTile(TileType type, std::string tileCode, float xTopSx, float yTopSx) {
    Tile *tile;
    bool crossable, destructible;
    int damage;
    if (type == TileType::columnRockTile) {
        destructible = false;
        crossable = false;
        damage = 2;
    }
    if (type == TileType::topRockTile) {
        destructible = false;
        crossable = false;
        damage = 0;
    }
    if (type == TileType::tipsRockTile) {
        destructible = true;
        crossable = false;
        damage = 3;
    }
    if (type == TileType::lavaTile) {
        destructible = false;
        crossable = true;
        damage = 50;
    }
    if (type == TileType::backgroundTile) {
        destructible = false;
        crossable = true;
        damage = 0;
    }
    tile = new Tile(crossable, destructible, damage, std::move(tileCode), xTopSx, yTopSx);
    return tile;
}
