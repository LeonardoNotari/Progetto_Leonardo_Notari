//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_ENEMY_H
#define PROGETTO_LEONARDO_NOTARI_ENEMY_H


class Enemy {
public:
    Enemy(int enemyX, int enemyY,int  enemyPower);

    virtual void Move(int gamecharacterX, int gamecharacterY) = 0;

    virtual int Attack(int gamecharacterX, int gamecharacterY) = 0;

protected:
    int posX;
    int posY;
    int damage;
};


#endif //PROGETTO_LEONARDO_NOTARI_ENEMY_H
