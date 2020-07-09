//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_ENEMY_H
#define PROGETTO_LEONARDO_NOTARI_ENEMY_H


class Enemy {
public:
    Enemy(int enemyX, int enemyY, int enemyPower);

    virtual void move(int gamecharacterX, int gamecharacterY) = 0;

    virtual int attack(int gamecharacterX, int gamecharacterY) = 0;

    int getEnemyX() const;

    int getEnemyY() const;

protected:
    int posX;
    int posY;
    int damage;
};


#endif //PROGETTO_LEONARDO_NOTARI_ENEMY_H
