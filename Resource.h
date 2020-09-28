//
// Created by leonardo on 17/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__RESOURCE_H
#define PROGETTO_LEONARDO_NOTARI__RESOURCE_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class TypeOfSprite {
    Player, KEnemy, CEnemy, BGun, LGun, MGun, LifePU, EnergyPU,CommonBulletSprite,LaserBulletSprite,BazookaBulletSprite
};

class Resource {
public:
    static Resource *getInstance();

    ~Resource() = default;

    sf::Sprite setSprite(TypeOfSprite spriteType);

private:
    static Resource *instance;
    std::map<TypeOfSprite,sf::Texture> textures;
    Resource();
};


#endif //PROGETTO_LEONARDO_NOTARI__RESOURCE_H
