//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"

class GameCharacter{
public:
    GameCharacter();
private:
    int  posX;
    int  posY;
    std::string  name;
    Weapon*  weapon   {nullptr};
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
