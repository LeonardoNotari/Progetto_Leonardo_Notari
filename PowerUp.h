//
// Created by leonardo on 26/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__POWERUP_H
#define PROGETTO_LEONARDO_NOTARI__POWERUP_H
#include <SFML/Graphics.hpp>
#include "Observer.h"

enum class PowerUpType {
    Energy, Life
};


class PowerUp: public Observer{
public:
    PowerUp(float x, float y, int increment, sf::Sprite itemSprite, PowerUpType itemType);

    int getEffect() const;

    float getX() const;

    float getY() const;

    void update(const std::string& goalReach) override;

    PowerUpType getType() const;

    sf::Sprite sprite;

    bool used;

protected:
    float posX;
    float posY;
    int effect;
    PowerUpType type;
};


#endif //PROGETTO_LEONARDO_NOTARI__POWERUP_H
