//
// Created by leono on 22/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_WEAPON_H
#define PROGETTO_LEONARDO_NOTARI_WEAPON_H

class Weapon {
public:
    int power;

    explicit Weapon(int basicWeaponPower);

    Weapon(int weaponPower, int weaponCost, int weaponX, int weaponY);

    virtual void Use();

    int getWeaponCost() const;

    int getWeaponX() const;

    int getWeaponY() const;

protected:
    int cost;
    int posX;
    int posY;
};

#endif //PROGETTO_LEONARDO_NOTARI_WEAPON_H

