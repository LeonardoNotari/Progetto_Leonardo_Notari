//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
#define PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H

#include "Enemy.h"


class KamikazeEnemy : virtual public Enemy {
public:
    KamikazeEnemy(int enemyX,int enemyY, int enemyPower);

    void Move(int gamecharacterX, int gamecharacterY) override;

    int Attack(int gamecharacterX, int gamecharacterY) override;

};


#endif //PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
