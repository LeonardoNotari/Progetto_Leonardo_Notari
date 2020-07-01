//
// Created by leono on 22/06/2020.
//

#include "Weapon.h"

Weapon::Weapon(int   basicWeaponPower):   power(basicWeaponPower),  cost(0){}

Weapon::Weapon(int   weaponPower,int   weaponCost):   power(weaponPower),   cost(weaponCost){}

int   Weapon::getWeaponCost()   const   {
    return   this->cost;
}

int   Weapon::getWeaponX()   const   {
    return   this->posX;
}

int   Weapon::getWeaponY()   const   {
    return   this->posY;
}