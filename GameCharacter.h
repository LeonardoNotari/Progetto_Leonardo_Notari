//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include <list>
#include "Weapon.h"
#include "Tile.h"
#include "Subject.h"
#include "Observer.h"
#include "Character.h"

class GameCharacter : public Character, public Subject {
public:

    GameCharacter(int gameCharacterHP, float gameCharacterX, float gameCharacterY, int spaceshipEnergy,
                  sf::Sprite playerSprite);

    void equipWeapon(Weapon *weapon);

    Weapon *getWeapon() const;

    int getEnergy() const;

    int getScore() const;

    float getXMax() const;

    float getXMin() const;

    void move(float x, float y,const TileMap& map) override;

    void setEnergy(int incremento);

    void setEnemyDefeated();

    float getEnemyDefeated() const;

    void reset(int playerEnergy,int hp,float x,float y);

    void subscribe(Observer* o) override;

    void unsubscribe(Observer* o) override;

    void notify(const std::string& goalReach) override;

    std::string getGoal();

    void setGoal();

    void setScore(int increment);

protected:
    bool isPossibleEquipWeapon(int cost) const;
    std::list<Observer*> observers;
    Weapon *weapon{nullptr};
    int energy;
    int weaponEquipped;
    std::string goal{" "};
    float xMax{8192};
    float xMin{20};
    float yMax{768};
    float enemyDefeated;
    int score;
    int travel;
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
