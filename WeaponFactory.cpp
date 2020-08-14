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
        bullets = 700;
        cadence = 50;
        range = 500;
        power = 100;
        cost = 200;
    }
    if (type == WeaponType::Bazooka) {
        bullets = 30;
        cadence = 800;
        range = 5000;
        power = 2000;
        cost = 200;
    }
    if (type == WeaponType::LaserGun) {
        bullets = 1000;
        cadence = 10;
        range = 1000;
        power = 20;
        cost = 200;
    }
    sf::Sprite W;
    W.setTexture(weaponTexture);
    weapon = new Weapon(power, cost, x, y, W, cadence, range, bullets);
    weapon->sprite.setPosition(sf::Vector2f(x, y));
    return weapon;
}