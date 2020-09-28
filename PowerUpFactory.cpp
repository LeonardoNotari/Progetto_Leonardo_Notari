//
// Created by leonardo on 28/09/20.
//
#include "PowerUp.h"
#include "Resource.h"
#include "PowerUpFactory.h"

PowerUp *PowerUpFactory::createPowerUp(PowerUpType type,float x,float y) {
    PowerUp *powerUp;
    sf::Sprite sprite;
    int increment;
    if (type == PowerUpType::Energy) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::EnergyPU);
        increment = 100;
    }
    if (type == PowerUpType::Life) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::LifePU);
        increment = 300;
    }
    powerUp = new PowerUp(x, y, increment, sprite, type);
    powerUp->sprite.setPosition(sf::Vector2f(powerUp->getX(), powerUp->getY()));
    return powerUp;
}
