//
// Created by leonardo on 09/07/20.
//

#include <gtest/gtest.h>
#include "../GameCharacter.h"
#include "../KamikazeEnemy.h"


TEST(KamikazeEnemy , Move) {
    GameCharacter player(8, 10);
    KamikazeEnemy alien(3, 3, 0);
    alien.Move(0,0);
    alien.Move(0,0);
    alien.Move(0,0);
    ASSERT_EQ(alien.getEnemyX(),0);
    ASSERT_EQ(alien.getEnemyY(),0);
}