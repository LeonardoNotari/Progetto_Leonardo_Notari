//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "Weapon.h"
#include "WeaponFactory.h"


Weapon *WeaponFactory::createWeapon(WeaponType type, float x, float y, const sf::Texture &weaponTexture,
                                    std::list<sf::Sprite> &sprites) {
    Weapon *weapon;
    sf::Sprite W;
    W.setTexture(weaponTexture);
    weapon = new Weapon(0, 0, x, y);
    W.setPosition(sf::Vector2f(x, y));
    sprites.push_back(W);
    weapon->spriteCode = sprites.size();
    return weapon;
}