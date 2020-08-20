//
// Created by leonardo on 19/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
#include "Tile.h"
enum class TileType{
    lavaTile,topRockTile,tipsRockTile,backgroundTile
};

class TileFactory {
public:
    virtual Tile *createTile(TileType type,std::string tileCode,float xTopDx,float yTopDx);
};


#endif //PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
