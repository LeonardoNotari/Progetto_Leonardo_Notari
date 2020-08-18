//
// Created by leonardo on 09/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_BULLET_H
#define PROGETTO_LEONARDO_NOTARI_BULLET_H

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameCharacter.h"
#include "Enemy.h"


class bullet {
public:
    bullet(int power, bool verse, float x, float y, sf::Sprite bulletSprite, int bulletRange);

    void move(float increment);

    bool bulletVerse;
    float bulletX, bulletY;
    int damage;
    sf::Sprite sprite;
    int bulletLife{0};
    int range;
};


#endif //PROGETTO_LEONARDO_NOTARI_BULLET_H
