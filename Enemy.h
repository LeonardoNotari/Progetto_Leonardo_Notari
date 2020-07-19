//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_ENEMY_H
#define PROGETTO_LEONARDO_NOTARI_ENEMY_H

#include "GameCharacter.h"

class Enemy {
public:
    int spriteCode;

    Enemy(float enemyX, float enemyY, int enemyPower, float enemySpeed);

    virtual~Enemy();

    virtual void move(float gamecharacterX, float gamecharacterY) = 0;

    virtual bool attack(GameCharacter &player) = 0;

    void receiveDamage(int damage);

    float getEnemyX() const;

    float getEnemyY() const;

    int getEnemyHP() const;

protected:
    int hp = 100;
    float posX;
    float posY;
    int damage;
    float speed;
};


#endif //PROGETTO_LEONARDO_NOTARI_ENEMY_H
