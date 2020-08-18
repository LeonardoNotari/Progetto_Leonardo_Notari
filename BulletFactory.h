//
// Created by leonardo on 20/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H

#include <SFML/Graphics.hpp>
#include "bullet.h"

class BulletFactory {
public:


    virtual bullet *
    createBullet(const Character &character, int power, bool verse, const sf::Texture &bulletTexture, int bulletRange);
};


#endif //PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
