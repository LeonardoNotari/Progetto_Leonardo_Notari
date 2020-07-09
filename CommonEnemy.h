//
// Created by leonardo on 06/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H
#define PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H

#include "Enemy.h"

class CommonEnemy : public Enemy {
public:
    CommonEnemy(int enemyX, int enemyY, int enemyPower);

    void move(int gamecharacterX, int gamecharacterY) override;
};


#endif //PROGETTO_LEONARDO_NOTARI_COMMONENEMY_H
