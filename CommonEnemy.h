//
// Created by leonardo on 06/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H
#define PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H

#include "Enemy.h"
#include "GameCharacter.h"

class CommonEnemy : public Enemy {
public:
    CommonEnemy(float enemyX, float enemyY, int enemyPower, float enemySpeed, sf::Sprite enemySprite);

    void move(float gamecharacterX, float gamecharacterY) override;

    void attack(GameCharacter &player, bool &enemyHasWeapon) override;
};


#endif //PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H
