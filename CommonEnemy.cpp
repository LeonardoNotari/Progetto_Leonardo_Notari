//
// Created by leonardo on 06/07/20.
//

#include "CommonEnemy.h"
#include "GameCharacter.h"


CommonEnemy::CommonEnemy(float enemyX, float enemyY, int enemyPower, float enemySpeed) : Enemy(enemyX, enemyY,
                                                                                               enemyPower,
                                                                                               enemySpeed) {}

void CommonEnemy::move(float gamecharacterX, float gamecharacterY) {
    if (posX < gamecharacterX - 200 || (posX > gamecharacterX && posX < gamecharacterX + 200)) {
        posX += speed;
    }
    if (posX > gamecharacterX + 200 || (posX < gamecharacterX && posX > gamecharacterX - 200)) {
        posX -= speed;
    }
    if (posY < gamecharacterY)
        posY += speed;
    if (posY > gamecharacterY)
        posY -= speed;
}

bool CommonEnemy::attack(GameCharacter &player) {

    if (posY == player.getGameCharacterY())
        damage = 0;
    return true;
}

