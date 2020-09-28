//
// Created by leonardo on 20/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__WEAPONFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__WEAPONFACTORY_H

#include "Weapon.h"

class WeaponFactory {
public:
    virtual Weapon *
    createWeapon(WeaponType type, float x, float y, int level);
};


#endif //PROGETTO_LEONARDO_NOTARI__WEAPONFACTORY_H
