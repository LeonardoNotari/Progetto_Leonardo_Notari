//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_ENEMY_H
#define PROGETTO_LEONARDO_NOTARI_ENEMY_H

#include <SFML/Graphics.hpp>
#include "GameCharacter.h"
#include "Character.h"


class Enemy : public Character , public Observer {
public:

    Enemy(int enemyHP, float enemyX, float enemyY, int enemyPower, float enemySpeed, sf::Sprite enemySprite);

    void move(float gamecharacterX, float gamecharacterY,const TileMap& map) override = 0;

    virtual void attack(GameCharacter &player, bool &enemyHasWeapon) = 0;

    int getEnemyDamage() const;

    int cadenceOfBullet{0};

    void update(const std::string& goalReach) override;

protected:
    int damage;
    float speed;
};


#endif //PROGETTO_LEONARDO_NOTARI_ENEMY_H
