//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
#include "BulletFactory.h"


bullet *BulletFactory::createBullet(const Character& character,BulletType type, int power, bool verse, const sf::Texture &bulletTexture, int bulletRange) {
    bullet *bullet = nullptr;
    sf::Sprite B;
    if (type == BulletType::Common) {
        B.setTexture(bulletTexture);
        bullet = new class bullet(power, verse,character.getX(),character.getY(), B, bulletRange);
    }
    bullet->sprite.setPosition(sf::Vector2f(character.getX(), character.getY()));
    return bullet;
}