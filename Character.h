//
// Created by leonardo on 26/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__CHARACTER_H
#define PROGETTO_LEONARDO_NOTARI__CHARACTER_H

#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Character {
public:
    Character(int hp, float x, float y, sf::Sprite characterSprite);

    virtual ~Character();

    virtual void move(float x, float y,const TileMap& map) = 0;

    float getX() const;

    float getY() const;

    int getHP() const;

    void receiveDamage(int damage);

    sf::Sprite sprite;

protected:
    float posX;
    float posY;
    int HP;
};


#endif //PROGETTO_LEONARDO_NOTARI__CHARACTER_H
