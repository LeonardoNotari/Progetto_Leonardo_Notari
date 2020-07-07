//
// Created by leonardo on 04/07/20.
//
#include "KamikazeEnemy.h"

KamikazeEnemy::KamikazeEnemy(int enemyX,int enemyY, int enemyPower) : Enemy(enemyX, enemyY, enemyPower){}

void KamikazeEnemy::Move(int gamecharacterX, int gamecharacterY) {
    if (posX < gamecharacterX)
        posX++;
    else
        posX--;
    if (posY < gamecharacterX)
        posY++;
    else
        posY--;
}

int KamikazeEnemy::Attack(int gamecharacterX, int gamecharacterY) {
    if (posX == gamecharacterX && posY == gamecharacterY)
        return damage;
    else
        return 0;
}