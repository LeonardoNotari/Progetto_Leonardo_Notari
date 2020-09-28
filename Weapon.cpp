//
// Created by leono on 22/06/2020.
//
#include <utility>
#include "Weapon.h"


Weapon::Weapon(int basicWeaponPower, int weaponCadence, int weaponRange) : power(basicWeaponPower), cost(0),
                                                                           cadence(weaponCadence), range(weaponRange),
                                                                           bullet(-1), type(WeaponType::Common) {}

Weapon::Weapon(int weaponPower, int weaponCost, float weaponX, float weaponY, sf::Sprite weaponSprite,
               int weaponCadence, int weaponRange, int weaponBullet, WeaponType weaponType) : power(weaponPower),
                                                                                              cost(weaponCost),
                                                                                              posX(weaponX),
                                                                                              posY(weaponY),
                                                                                              sprite(std::move(
                                                                                                      weaponSprite)),
                                                                                              cadence(weaponCadence),
                                                                                              range(weaponRange),
                                                                                              bullet(weaponBullet),
                                                                                              type(weaponType) {}

int Weapon::getWeaponCost() const {
    return cost;
}

float Weapon::getWeaponX() const {
    return posX;
}

float Weapon::getWeaponY() const {
    return posY;
}

int Weapon::getWeaponPower() const {
    return power;
}

int Weapon::getWeaponBullet() const {
    return bullet;
}

void Weapon::setWeaponBullet() {
    bullet--;
}

int Weapon::getWeaponCadence() const {
    return cadence;
}

int Weapon::getWeaponRange() const {
    return range;
}

void Weapon::update(const std::string &goalReach) {
    if (goalReach == "EquipGoal1")
        power *= 2;
    if (goalReach == "EquipGoal2")
        power *= 5;
    if (goalReach == "EquipGoal1")
        power *= 10;
}