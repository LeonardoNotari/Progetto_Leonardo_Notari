//
// Created by leonardo on 04/07/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI_ENEMY_H
#define PROGETTO_LEONARDO_NOTARI_ENEMY_H


class Enemy {
public:
    Enemy();
    void   Move();
    void   Attack();
    void   ReceiveDamage();
private:
    int   posX;
    int   posY;
    int   hp;
    int   damage;

};


#endif //PROGETTO_LEONARDO_NOTARI_ENEMY_H
