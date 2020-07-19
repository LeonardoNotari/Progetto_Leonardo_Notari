//
// Created by leonardo on 06/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H
#define PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H

#include "Enemy.h"
#include "GameCharacter.h"

class CommonEnemy : public Enemy {
public:
    CommonEnemy(float enemyX, float enemyY, int enemyPower, float enemySpeed);

    void move(float gamecharacterX, float gamecharacterY) override;

    bool attack(GameCharacter &player) override;
};


#endif //PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H
