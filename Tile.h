//
// Created by leonardo on 19/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__TILE_H
#define PROGETTO_LEONARDO_NOTARI__TILE_H

#include <iostream>

class Tile {
public:
    Tile(bool tileCrossable, bool tileDestructible, int damage, std::string tileCode, float xTopSx, float yTopSx);

    bool getIsCrossable() const;

    bool getIsDestructible() const;

    int getDamage() const;

    void destroyTile();

    std::string code;
    float xVertexTopSx;
    float yVertexTopSx;
private:
    bool crossable;
    bool destructible;
    int damageIfHit;
};


#endif //PROGETTO_LEONARDO_NOTARI__TILE_H
