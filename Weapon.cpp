//
// Created by leono on 22/06/2020.
//
#include <list>
#include "bullet.h"
#include "Weapon.h"

Weapon::Weapon(int basicWeaponPower) : power(basicWeaponPower), cost(0) {}

Weapon::Weapon(int weaponPower, int weaponCost, float weaponX, float weaponY) : power(weaponPower), cost(weaponCost),
                                                                                posX(weaponX), posY(weaponY) {}

int Weapon::getWeaponCost() const {
    return this->cost;
}

float Weapon::getWeaponX() const {
    return this->posX;
}

float Weapon::getWeaponY() const {
    return this->posY;
}

int Weapon::getWeaponPower() const {
    return this->power;
}

void Weapon::use() {

}

