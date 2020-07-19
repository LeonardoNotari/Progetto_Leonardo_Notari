//
// Created by leono on 22/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_WEAPON_H
#define PROGETTO_LEONARDO_NOTARI_WEAPON_H

class Weapon {
public:
    int spriteCode;

    explicit Weapon(int basicWeaponPower);

    Weapon(int weaponPower, int weaponCost, float weaponX, float weaponY);

    virtual void use();

    int getWeaponCost() const;

    float getWeaponX() const;

    float getWeaponY() const;

    int getWeaponPower() const;

protected:
    int power;
    int cost;
    float posX;
    float posY;
};

#endif //PROGETTO_LEONARDO_NOTARI_WEAPON_H

