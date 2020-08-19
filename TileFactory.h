//
// Created by leonardo on 19/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
enum class TileType{
    lavaTile,topRockTile,tipsRockTile,backgroundTile
};

class TileFactory {
public:
    virtual Tile *createTile(TileType type, float x, float y);
};


#endif //PROGETTO_LEONARDO_NOTARI__TILEFACTORY_H
