//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "KamikazeEnemy.h"
#include "CommonEnemy.h"
#include "EnemyFactory.h"


Enemy *EnemyFactory::createEnemy(EnemyType type, const sf::Texture &enemyTexture, float X, float Y, float speed,
                                 std::list<sf::Sprite> &sprites) {
    Enemy *enemy = nullptr;
    sf::Sprite E;
    if (type == EnemyType::Kamikaze) {
        E.setTexture(enemyTexture);
        enemy = new KamikazeEnemy(X, Y, 50, speed);
    } else if (type == EnemyType::Common) {
        E.setTexture(enemyTexture);
        enemy = new CommonEnemy(X, Y, 50, speed);
    }
    E.setPosition(sf::Vector2f(enemy->getEnemyX(), enemy->getEnemyX()));
    sprites.push_back(E);
    enemy->spriteCode = sprites.size();
    return enemy;
}