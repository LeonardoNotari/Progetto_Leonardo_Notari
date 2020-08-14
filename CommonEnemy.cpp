//
// Created by leonardo on 06/07/20.
//

#include "CommonEnemy.h"

#include <utility>
#include "GameCharacter.h"


CommonEnemy::CommonEnemy(int enemyHP,float enemyX, float enemyY, int enemyPower, float enemySpeed, sf::Sprite enemySprite) : Enemy(enemyHP,enemyX,enemyY,enemyPower,enemySpeed,std::move(enemySprite)){}

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

void CommonEnemy::attack(GameCharacter &player, bool &enemyHasWeapon) {
    if (player.getY() <= this->posY + 1 && player.getY() >= this->posY - 1)
        enemyHasWeapon = true;
}

