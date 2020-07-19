//
// Created by leonardo on 04/07/20.
//

#include "Enemy.h"


Enemy::Enemy(float enemyX, float enemyY, int enemyPower, float enemySpeed) : posX(enemyX), posY(enemyY),
                                                                             damage(enemyPower), speed(enemySpeed) {}

Enemy::~Enemy() {
    delete this;
}

float Enemy::getEnemyX() const {
    return this->posX;
}

float Enemy::getEnemyY() const {
    return this->posY;
}

int Enemy::getEnemyHP() const {
    return this->hp;
}

void Enemy::receiveDamage(int enemyDamage) {
    this->hp -= enemyDamage;
}