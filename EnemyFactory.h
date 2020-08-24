//
// Created by leonardo on 20/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__ENEMYFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__ENEMYFACTORY_H

#include <bits/unique_ptr.h>
#include "Enemy.h"

enum class EnemyType {
    Kamikaze, Common
};


class EnemyFactory {

public:


    virtual Enemy *createEnemy(EnemyType type, const sf::Texture &enemyTexture, float X, float Y, float speed,int level);
};


#endif //PROGETTO_LEONARDO_NOTARI__ENEMYFACTORY_H
