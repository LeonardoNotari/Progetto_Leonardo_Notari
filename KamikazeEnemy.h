//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
#define PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H

#include "Enemy.h"


class KamikazeEnemy : virtual public Enemy {
public:
    KamikazeEnemy(int enemyX, int enemyY, int enemyPower);

    void move(int gamecharacterX, int gamecharacterY) override;

    int attack(int gamecharacterX, int gamecharacterY) override;

};


#endif //PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
