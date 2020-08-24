//
// Created by leonardo on 26/07/20.
//
#include "Tile.h"
#include "Character.h"

Character::Character(int hp, float x, float y, sf::Sprite characterSprite) : HP(hp), posX(x), posY(y),
                                                                             sprite(std::move(characterSprite)) {}

Character::~Character() {
    delete this;
}

float Character::getX() const {
    return this->posX;
}

float Character::getY() const {
    return this->posY;
}

int Character::getHP() const {
    return this->HP;
}

void Character::receiveDamage(int damage) {
    this->HP -= damage;
}

bool Character::isLegalMove(std::vector<Tile *> tiles, float x, float y) {
    auto it = tiles.begin();
    Tile *tile;
    //bool inside=false;
    tile = *it;
    while (this->posX + x < tile->xVertexTopSx || this->posX + x > tile->xVertexTopSx + 64 ||
              this->posY + y < tile->yVertexTopSx || this->posY + y > tile->yVertexTopSx + 64){
        /*if(this->posX + x > tile->xVertexTopSx && this->posX + x < tile->xVertexTopSx + 64 &&
         this->posY + y > tile->yVertexTopSx && this->posY + y < tile->yVertexTopSx + 64)
            inside=true;*/
        tile = *it;
        it++;
    }
    receiveDamage(tile->getDamage());
    return tile->getIsCrossable();
}
