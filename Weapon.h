//
// Created by leono on 22/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_WEAPON_H
#define PROGETTO_LEONARDO_NOTARI_WEAPON_H

class Weapon{
public:
    int  cost;
    Weapon (int basicWeaponPower);
    Weapon (int   weaponPower,int   weaponCost);
protected:
    int  power;
};

#endif //PROGETTO_LEONARDO_NOTARI_WEAPON_H

