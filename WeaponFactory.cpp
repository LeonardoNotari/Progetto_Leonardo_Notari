//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "Weapon.h"
#include "Resource.h"
#include "WeaponFactory.h"


Weapon *WeaponFactory::createWeapon(WeaponType type, float x, float y, int level) {
    Weapon *weapon;
    sf::Sprite sprite;
    int bullets, cadence, range, power, cost;
    if (type == WeaponType::MachineGun) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::MGun);
        bullets = 500;
        cadence = 50;
        range = 300;
        power = 100;
        cost = 100;
    }
    if (type == WeaponType::Bazooka) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::BGun);
        bullets = 50;
        cadence = 500;
        range = 2000;
        power = 2000;
        cost = 100;
    }
    if (type == WeaponType::LaserGun) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::LGun);
        bullets = 1000;
        cadence = 5;
        range = 300;
        power = 30;
        cost = 100;
    }
    weapon = new Weapon(power * level, cost * level, x, y, sprite, cadence, range, bullets, type);
    weapon->sprite.setPosition(sf::Vector2f(x, y));
    return weapon;
}