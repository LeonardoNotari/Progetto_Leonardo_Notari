//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"
#include "Character.h"

class GameCharacter: public Character {
public:

    GameCharacter(int gameCharacterHP,float gameCharacterX,float gameCharacterY, int spaceshipEnergy, sf::Sprite playerSprite);

    ~GameCharacter();

    void equipWeapon(Weapon *weapon);

    Weapon *getWeapon() const;

    int getEnergy() const;

    float getXMax() const;

    float getXMin() const;

    void move(float x, float y) override;

    void setEnergy(int incremento);

protected:
    bool isPossibleEquipWeapon(int cost) const;
    Weapon *weapon{nullptr};
    int energy;
    //int freeEnergy {energy}; FIXME se si vuole poter equipaggiare piu armi
    std::string name;
    float xMax{8192};
    float xMin{0};
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
