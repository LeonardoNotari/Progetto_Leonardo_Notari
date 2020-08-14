//
// Created by leonardo on 20/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H

#include <SFML/Graphics.hpp>
#include "bullet.h"

enum class BulletType {
    Common
};

class BulletFactory {
public:


    virtual bullet *
    createBullet(const Character &character,BulletType type, int power, bool verse, const sf::Texture &bulletTexture, int bulletRange);
};


#endif //PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
