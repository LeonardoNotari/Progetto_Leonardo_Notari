//
// Created by leonardo on 19/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H

#include "Tile.h"

enum class TileType {
    lavaTile, topRockTile, tipsRockTile, backgroundTile,columnRockTile
};

class TileFactory {
public:
    virtual Tile *createTile(TileType type, std::string tileCode, float xTopSx, float yTopSx);
};


#endif //PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
