//
// Created by leonardo on 04/07/20.
//
#include "KamikazeEnemy.h"
#include "GameCharacter.h"

KamikazeEnemy::KamikazeEnemy(float enemyX, float enemyY, int enemyPower, float enemySpeed) : Enemy(enemyX, enemyY,
                                                                                                   enemyPower,
                                                                                                   enemySpeed) {}

void KamikazeEnemy::move(float gamecharacterX, float gamecharacterY) {
    if (posX < gamecharacterX)
        posX += speed;
    else
        posX -= speed;
    if (posY < gamecharacterY)
        posY += speed;
    else
        posY -= speed;
}

bool KamikazeEnemy::attack(GameCharacter &player) {
    if (posX > player.getGameCharacterX() - 1 && posX < player.getGameCharacterY() - 1 &&
        posY > player.getGameCharacterX() - 1 && posY < player.getGameCharacterY() - 1) {
        player.receiveDamage(damage);
        return true;
    }
    return false;
}