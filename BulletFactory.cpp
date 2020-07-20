//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "bullet.h"
#include "BulletFactory.h"


bullet *BulletFactory::createBullet(BulletType type, bool verse, const sf::Texture &bulletTexture, float X, float Y,
                                    std::list<sf::Sprite> &sprites) {
    bullet *bullet = nullptr;
    sf::Sprite B;
    if (type == BulletType::Common) {
        B.setTexture(bulletTexture);
        bullet = new class bullet(0, verse, X, Y);
    }
    B.setPosition(sf::Vector2f(X, Y));
    sprites.push_back(B);
    bullet->spriteCode = sprites.size();
    return bullet;
}