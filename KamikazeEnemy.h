//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
#define PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H

#include "Enemy.h"
#include "GameCharacter.h"


class KamikazeEnemy : virtual public Enemy {
public:
    KamikazeEnemy(float enemyX, float enemyY, int enemyPower, float speed,sf::Sprite enemySprite);

    void move(float gamecharacterX, float gamecharacterY) override;

    void attack(GameCharacter &player,bool &enemyHasWeapon) override;

};


#endif //PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
