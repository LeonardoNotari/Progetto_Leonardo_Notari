//
// Created by leonardo on 04/07/20.
//

#include "Enemy.h"

#include <utility>


Enemy::Enemy(float enemyX, float enemyY, int enemyPower, float enemySpeed, sf::Sprite enemySprite) : posX(enemyX),
                                                                                                     posY(enemyY),
                                                                                                     damage(enemyPower),
                                                                                                     speed(enemySpeed),
                                                                                                     sprite(std::move(
                                                                                                             enemySprite)) {}

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

int Enemy::getEnemyDamage() const {
    return this->damage;
}
