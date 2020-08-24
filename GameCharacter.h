//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"
#include "Tile.h"
#include "Character.h"

class GameCharacter : public Character {
public:

    GameCharacter(int gameCharacterHP, float gameCharacterX, float gameCharacterY, int spaceshipEnergy,
                  sf::Sprite playerSprite);

    void equipWeapon(Weapon *weapon);

    Weapon *getWeapon() const;

    int getEnergy() const;

    float getXMax() const;

    float getXMin() const;

    void move(float x, float y,std::vector<Tile *> tiles) override;

    void setEnergy(int incremento);

    void reset(int playerEnergy,int hp,float x,float y);

protected:
    bool isPossibleEquipWeapon(int cost) const;

    Weapon *weapon{nullptr};
    int energy;
    //int freeEnergy {energy}; FIXME se si vuole poter equipaggiare piu armi
    std::string name;
    float xMax{8192};
    float xMin{20};
    float yMax{768};
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
