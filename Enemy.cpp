//
// Created by leonardo on 04/07/20.
//

#include "Enemy.h"


Enemy::Enemy(int enemyX, int enemyY, int enemyPower) : posX(enemyX), posY(enemyY), damage(enemyPower) {}

int Enemy::getEnemyX() const {
    return this->posX;
}

int Enemy::getEnemyY() const {
    return this->posY;
}