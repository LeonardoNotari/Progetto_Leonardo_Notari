//
// Created by leonardo on 26/07/20.
//
#include "Tile.h"
#include "Character.h"

Character::Character(int hp, float x, float y, sf::Sprite characterSprite) : HP(hp), posX(x), posY(y),
                                                                             sprite(std::move(characterSprite)) {}

Character::~Character() = default;


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


