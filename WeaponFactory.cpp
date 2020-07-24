//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "Weapon.h"
#include "WeaponFactory.h"


Weapon *WeaponFactory::createWeapon(WeaponType type, float x, float y, const sf::Texture &weaponTexture) {
    Weapon *weapon;
    int bullets, cadence, range, power, cost;
    if (type == WeaponType::MachineGun) {
        bullets = 10000;
        cadence = 50;
        range = 5000;
        power = 100;
        cost = 0;
    }
    if (type == WeaponType::Bazooka) {
        bullets = 100;
        cadence = 500;
        range = 5000;
        power = 1000;
        cost = 0;
    }
    if (type == WeaponType::LaserGun) {
        bullets = 10000;
        cadence = 0;
        range = 10000;
        power = 50;
        cost = 0;
    }
    sf::Sprite W;
    W.setTexture(weaponTexture);
    weapon = new Weapon(power, cost, x, y, W, cadence, range, bullets);
    weapon->sprite.setPosition(sf::Vector2f(x, y));
    return weapon;
}