//
// Created by leonardo on 09/07/20.
//

#include <utility>
#include <SFML/Graphics.hpp>
#include "bullet.h"


bullet::bullet(int power, bool verse, float x, float y,sf::Sprite  bulletSprite) : damage(power), bulletVerse(verse), bulletX(x), bulletY(y), sprite(std::move(bulletSprite)) {}


void bullet::move(float increment) {
    this->bulletLife++;
    this->bulletX += increment;
}
