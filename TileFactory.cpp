//
// Created by leonardo on 19/08/20.
//
#include "Tile.h"
#include "TileFactory.h"

#include <utility>


Tile *TileFactory::createTile(TileType type,std::string tileCode,float xTopDx,float yTopDx) {
    Tile *tile;
    bool crossable,destructible;
    int damage;
    if (type == TileType::topRockTile) {
        destructible = false;
        crossable = false;
        damage = 10;
    }
    if (type == TileType::tipsRockTile) {
        destructible = true;
        crossable = false;
        damage = 50;
    }
    if (type == TileType::lavaTile) {
        destructible = false;
        crossable = true;
        damage = 1000;
    }
    if (type == TileType::backgroundTile) {
        destructible = false;
        crossable = true;
        damage = 0;
    }
    tile = new Tile(crossable,destructible,damage,std::move(tileCode),xTopDx,yTopDx);
    return tile;
}
