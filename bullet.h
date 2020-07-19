//
// Created by leonardo on 09/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_BULLET_H
#define PROGETTO_LEONARDO_NOTARI_BULLET_H

#include <list>
#include <vector>
#include "GameCharacter.h"
#include "Enemy.h"

class bullet {
public:
    bullet(int power, bool verse, float x, float y);
    void move(float increment);
    bool bulletVerse;
    float bulletX, bulletY;
    int damage;
    int spriteCode;
    int bulletLife{0};
};


#endif //PROGETTO_LEONARDO_NOTARI_BULLET_H
