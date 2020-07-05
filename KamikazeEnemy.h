//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
#define PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H

#include "Enemy.h"


class KamikazeEnemy : virtual public Enemy {
public:
    KamikazeEnemy(int enemyX, int enemyY);

    void Move(int gamecharacterX, int gamecharacterY) override;

    int Attack(int gamecharacterX, int gamecharacterY) override;

private:
    int posX;
    int posY;
    int damage{7};
};


#endif //PROGETTO_LEONARDO_NOTARI_KAMIKAZEENEMY_H
