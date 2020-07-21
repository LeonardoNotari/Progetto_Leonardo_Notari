//
// Created by leonardo on 20/07/20.
//
#include <SFML/Graphics.hpp>
#include <list>
#include "KamikazeEnemy.h"
#include "CommonEnemy.h"
#include "EnemyFactory.h"





Enemy *EnemyFactory::createEnemy(EnemyType type, const sf::Texture &enemyTexture, float X, float Y, float speed) {
    Enemy *enemy = nullptr;
    sf::Sprite E;
    if (type == EnemyType::Kamikaze) {
        E.setTexture(enemyTexture);
        enemy = new KamikazeEnemy(X, Y, 500, speed,E);
    } else if (type == EnemyType::Common) {
        E.setTexture(enemyTexture);
        enemy = new CommonEnemy(X, Y, 50, speed,E);
    }
    enemy->sprite.setPosition(sf::Vector2f(enemy->getEnemyX(), enemy->getEnemyX()));
    return enemy;
}