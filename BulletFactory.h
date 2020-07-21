//
// Created by leonardo on 20/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
enum class BulletType {
    Common
};

class BulletFactory {
public:


    virtual bullet *createBullet(BulletType type,int power, bool verse, const sf::Texture &bulletTexture, float X, float Y);
};


#endif //PROGETTO_LEONARDO_NOTARI__BULLETFACTORY_H
