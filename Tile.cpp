//
// Created by leonardo on 19/08/20.
//
#include <utility>
#include "Tile.h"

Tile::Tile(bool tileCrossable, bool tileDestructible, int damage, std::string tileCode, float xTopSx, float yTopSx)
        : crossable(tileCrossable), destructible(tileDestructible), damageIfHit(damage), code(std::move(tileCode)),
          xVertexTopSx(xTopSx), yVertexTopSx(yTopSx) {}

int Tile::getDamage() const {
    return damageIfHit;
}

bool Tile::getIsDestructible() const {
    return destructible;
}

bool Tile::getIsCrossable() const {
    return crossable;
}

void Tile::destroyTile() {
    destructible = false;
    crossable = true;
    damageIfHit = 0;
    code = "13";
}
