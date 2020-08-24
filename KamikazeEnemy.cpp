//
// Created by leonardo on 04/07/20.
//

#include "KamikazeEnemy.h"
#include "Character.h"
#include "GameCharacter.h"

KamikazeEnemy::KamikazeEnemy(int enemyHP, float enemyX, float enemyY, int enemyPower, float enemySpeed,
                             const sf::Sprite &enemySprite) : Enemy(enemyHP, enemyX, enemyY, enemyPower, enemySpeed,
                                                                    enemySprite) {}

void KamikazeEnemy::move(float gamecharacterX, float gamecharacterY,std::vector<Tile *> tiles) {
    if (isLegalMove(tiles, speed, 0)) {
        if (posX < gamecharacterX)
            posX += speed;
        else
            posX -= speed;
        if (posY < gamecharacterY)
            posY += speed;
        else
            posY -= speed;
    }else{
        if (posX > gamecharacterX)
            posX += speed;
        else
            posX -= speed;
        if (posY < gamecharacterY)
            posY += speed;
        else
            posY -= speed;
    }
}

void KamikazeEnemy::attack(GameCharacter &player, bool &enemyHasWeapon) {
    if (posX > player.getX() - 30 && posX < player.getX() + 30 &&
        posY > player.getY() - 30 && posY < player.getY() + 30) {
        player.receiveDamage(this->damage);
        this->HP = 0;
    }
    enemyHasWeapon = false;
}