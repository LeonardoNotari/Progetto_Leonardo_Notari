//
// Created by leonardo on 19/08/20.
//
#include <utility>
#include "Tile.h"

Tile::Tile(bool tileCrossable, bool tileDestructible, int damage, std::string tileCode, float xTopSx, float yTopSx)
        : crossable(tileCrossable), destructible(tileDestructible), damageIfHit(damage), code(std::move(tileCode)),
          xVertexTopSx(xTopSx), yVertexTopSx(yTopSx) {}

int Tile::getDamage() const {
    return this->damageIfHit;
}

bool Tile::getIsDestructible() const {
    return this->destructible;
}

bool Tile::getIsCrossable() const {
    return this->crossable;
}

void Tile::destroyTile() {
    this->destructible = false;
    this->crossable = true;
    this->damageIfHit = 0;
    this->code = "13";
}
