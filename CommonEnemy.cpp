//
// Created by leonardo on 06/07/20.
//

#include "CommonEnemy.h"

CommonEnemy::CommonEnemy(int enemyX, int enemyY, int enemyPower):Enemy(enemyX,enemyY,enemyPower){}

void CommonEnemy::Move(int gamecharacterX, int gamecharacterY) {
    if(posX<gamecharacterX-4)
        posX++;
    if(posX>gamecharacterX+4)
        posX--;
    if(posY<gamecharacterY)
        posX++;
    if(posY>gamecharacterY)
        posX--;
}

