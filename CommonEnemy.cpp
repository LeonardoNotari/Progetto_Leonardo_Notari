//
// Created by leonardo on 06/07/20.
//

#include "CommonEnemy.h"

#include <utility>
#include "GameCharacter.h"


CommonEnemy::CommonEnemy(int enemyHP, float enemyX, float enemyY, int enemyPower, float enemySpeed,
                         sf::Sprite enemySprite) : Enemy(enemyHP, enemyX, enemyY, enemyPower, enemySpeed,
                                                         std::move(enemySprite)) {}

void CommonEnemy::move(float gamecharacterX, float gamecharacterY, const TileMap &map) {
    int damage = 0;
    if (map.isLegalMove(posX, posY, speed, 0, damage)) {
        if (posX < gamecharacterX - 200 || (posX > gamecharacterX && posX < gamecharacterX + 200))
            posX += speed;
        if (posX > gamecharacterX + 200 || (posX < gamecharacterX && posX > gamecharacterX - 200))
            posX -= speed;
        if (posY < gamecharacterY)
            posY += speed;
        if (posY > gamecharacterY)
            posY -= speed;
    } else {
        if (posX > gamecharacterX)
            posX += speed;
        else
            posX -= speed;
        if (posY < gamecharacterY)
            posY += speed;
        else
            posY -= speed;
    }
    this->receiveDamage(damage);
}

void CommonEnemy::attack(GameCharacter &player, bool &enemyHasWeapon) {
    if (player.getY() <= posY + 3 && player.getY() >= posY - 3)
        enemyHasWeapon = true;
}

