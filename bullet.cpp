//
// Created by leonardo on 09/07/20.
//
#include <list>
#include <vector>
#include "bullet.h"
#include "GameCharacter.h"
#include "Enemy.h"

bullet::bullet(int power, bool verse, float x, float y) : damage(power), bulletVerse(verse), bulletX(x), bulletY(y) {}


void bullet::move(float increment) {
    bulletLife++;
    bulletX += increment;
}
