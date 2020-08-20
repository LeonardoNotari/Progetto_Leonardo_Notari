//
// Created by leonardo on 19/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__TILE_H
#define PROGETTO_LEONARDO_NOTARI__TILE_H
#include <iostream>
class Tile {
public:
    Tile(bool tileCrossable,bool tileDestructible,int damage,std::string tileCode,float xTopDx,float yTopDx);
    std::string code;
    float xVertexTopDx;
    float yVertexTopDx;
private:
    bool crossable;
    bool destructible;
    int damageIfHit;
};


#endif //PROGETTO_LEONARDO_NOTARI__TILE_H
