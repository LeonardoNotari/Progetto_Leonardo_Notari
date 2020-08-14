//
// Created by leonardo on 04/07/20.
//

#include "Enemy.h"

#include <utility>


Enemy::Enemy(int enemyHP,float enemyX, float enemyY, int enemyPower, float enemySpeed, sf::Sprite enemySprite) : Character(enemyHP,enemyX,enemyY,std::move(enemySprite)),
                                                                                                     damage(enemyPower),
                                                                                                     speed(enemySpeed){}




int Enemy::getEnemyDamage() const {
    return this->damage;
}
