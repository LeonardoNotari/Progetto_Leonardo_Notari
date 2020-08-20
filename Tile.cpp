//
// Created by leonardo on 19/08/20.
//

#include "Tile.h"

#include <utility>

Tile::Tile(bool tileCrossable,bool tileDestructible,int damage,std::string tileCode,float xTopDx,float yTopDx):crossable(tileCrossable),destructible(tileDestructible),damageIfHit(damage),code(std::move(tileCode)),xVertexTopDx(xTopDx), yVertexTopDx(yTopDx){}
