//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"

class GameCharacter {
public:

    GameCharacter(int spaceshipEnergy, int spaceshipHP);

    bool isPossibleEquipWeapon(int cost);

    void equipWeapon(int cost, Weapon *weapon);

    Weapon *getWeapon() const;

    float getGameCharacterX() const;

    float getGameCharacterY() const;

    void move(float x, float y);

    void receiveDamage(int damage);

    int getGameCharacterHP() const;

protected:
    Weapon *weapon{nullptr};
    float posX;
    float posY;
    int HP;
    int energy;
    int freeEnergy;
    std::string name;
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
