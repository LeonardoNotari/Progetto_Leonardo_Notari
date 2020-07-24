//
// Created by leonardo on 20/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__WEAPONFACTORY_H
#define PROGETTO_LEONARDO_NOTARI__WEAPONFACTORY_H
enum class WeaponType {
    Bazooka, MachineGun, LaserGun
};

class WeaponFactory {
public:
    virtual Weapon *
    createWeapon(WeaponType type, float x, float y, const sf::Texture &weaponTexture);
};


#endif //PROGETTO_LEONARDO_NOTARI__WEAPONFACTORY_H
