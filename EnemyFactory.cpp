//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "Resource.h"
#include "KamikazeEnemy.h"
#include "CommonEnemy.h"
#include "EnemyFactory.h"


Enemy *EnemyFactory::createEnemy(EnemyType type, float X, float Y, float speed, int level) {
    Enemy *enemy = nullptr;
    sf::Sprite sprite;
    if (type == EnemyType::Kamikaze) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::KEnemy);
        enemy = new KamikazeEnemy(100 * level, X, Y, 500, speed, sprite);
    } else if (type == EnemyType::Common) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::CEnemy);
        enemy = new CommonEnemy(300 * level, X, Y, 50, speed, sprite);
    }
    enemy->sprite.setPosition(sf::Vector2f(enemy->getX(), enemy->getY()));
    return enemy;
}