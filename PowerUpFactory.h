//
// Created by leonardo on 28/09/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__POWERUPFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__POWERUPFACTORY_H
#include "PowerUp.h"


class PowerUpFactory {
public:
    virtual PowerUp *createPowerUp(PowerUpType type,float x,float y);
};


#endif //PROGETTO_LEONARDO_NOTARI__POWERUPFACTORY_H
