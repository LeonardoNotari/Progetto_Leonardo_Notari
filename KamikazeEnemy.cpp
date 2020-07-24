//
// Created by leonardo on 04/07/20.
//
#include "KamikazeEnemy.h"

#include <utility>
#include "GameCharacter.h"

KamikazeEnemy::KamikazeEnemy(float enemyX, float enemyY, int enemyPower, float enemySpeed, sf::Sprite enemySprite)
        : Enemy(enemyX, enemyY,
                enemyPower,
                enemySpeed, std::move(enemySprite)) {}

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

void KamikazeEnemy::attack(GameCharacter &player, bool &enemyHasWeapon) {
    if (posX > player.getGameCharacterX() - 10 && posX < player.getGameCharacterY() + 10 &&
        posY > player.getGameCharacterX() - 10 && posY < player.getGameCharacterY() + 10) {
        player.receiveDamage(this->damage);
        this->hp = 0;
    }
    enemyHasWeapon = false;
}