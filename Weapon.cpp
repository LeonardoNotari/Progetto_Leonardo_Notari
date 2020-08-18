//
// Created by leono on 22/06/2020.
//
#include <utility>
#include "Weapon.h"


  Weapon::Weapon(int basicWeaponPower, int weaponCadence, int weaponRange) : power(basicWeaponPower), cost(0),
                                                                           cadence(weaponCadence), range(weaponRange),bullet(-1),type(WeaponType::Common){}

Weapon::Weapon(int weaponPower, int weaponCost, float weaponX, float weaponY, sf::Sprite weaponSprite,
               int weaponCadence, int weaponRange, int weaponBullet,WeaponType weaponType) : power(weaponPower), cost(weaponCost),
                                                                       posX(weaponX), posY(weaponY),sprite(std::move(weaponSprite))
                                                                       ,cadence(weaponCadence), range(weaponRange),
                                                                       bullet(weaponBullet),type(weaponType){}

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

int Weapon::getWeaponBullet() const {
    return this->bullet;
}

void Weapon::setWeaponBullet() {
    this->bullet--;
}

int Weapon::getWeaponCadence() const {
    return this->cadence;
}

int Weapon::getWeaponRange() const {
    return this->range;
}