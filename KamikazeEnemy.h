//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
#define PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H

#include "Enemy.h"
#include "GameCharacter.h"


class KamikazeEnemy : virtual public Enemy {
public:
    KamikazeEnemy(float enemyX, float enemyY, int enemyPower, float speed);

    void move(float gamecharacterX, float gamecharacterY) override;

    bool attack(GameCharacter &player) override;

};


#endif //PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
