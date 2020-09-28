//
// Created by leonardo on 26/07/20.
//
#include "PowerUp.h"

#include <utility>

PowerUp::PowerUp(float x, float y, int increment, sf::Sprite itemSprite, PowerUpType itemType) : posX(x), posY(y),
                                                                                                 effect(increment),
                                                                                                 sprite(std::move(
                                                                                                         itemSprite)),
                                                                                                 type(itemType),
                                                                                                 used(false) {}

int PowerUp::getEffect() const {
    {
        return this->effect;
    }
}

float PowerUp::getX() const {
    return this->posX;
}

float PowerUp::getY() const {
    return this->posY;
}

PowerUpType PowerUp::getType() const {
    return this->type;
}

//FIXME PROVA OBSERVER
void PowerUp::update(const std::string& goalReach) {
    if(goalReach=="TravelGoal1")
        this->effect=this->effect + 100;
    if(goalReach=="TravelGoal2")
        this->effect=this->effect + 200;
    if(goalReach=="TravelGoal3")
        this->effect=this->effect + 500;
}
