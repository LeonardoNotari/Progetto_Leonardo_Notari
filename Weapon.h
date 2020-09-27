//
// Created by leono on 22/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_WEAPON_H
#define PROGETTO_LEONARDO_NOTARI_WEAPON_H

#include <SFML/Graphics.hpp>
#include "Observer.h"

enum class WeaponType {
    MachineGun, LaserGun, Bazooka, Common
};

class Weapon: public Observer {
public:

    explicit Weapon(int basicWeaponPower, int weaponCadence, int weaponRange);

    Weapon(int weaponPower, int weaponCost, float weaponX, float weaponY, sf::Sprite weaponSprite, int weaponCadence,
           int weaponRange, int weaponBullet, WeaponType weaponType);

    int getWeaponCost() const;

    float getWeaponX() const;

    float getWeaponY() const;

    int getWeaponPower() const;

    int getWeaponCadence() const;

    int getWeaponBullet() const;

    void setWeaponBullet();

    int getWeaponRange() const;

    void update(const std::string& goalReach) override;

    bool equip{false};

    sf::Sprite sprite;

    WeaponType type;

protected:
    int bullet;
    int power;
    int cost;
    float posX{};
    float posY{};
    int range;
    int cadence;
};

#endif //PROGETTO_LEONARDO_NOTARI_WEAPON_H

