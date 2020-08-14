//
// Created by leonardo on 09/07/20.
//

#include <gtest/gtest.h>
#include "../GameCharacter.h"
#include "../KamikazeEnemy.h"
#include "../CommonEnemy.h"

TEST(Enemy, Move) {
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(0,0,0,0,spriteTest);
    KamikazeEnemy alien(0, 5,5,0, 0.5,spriteTest);
    CommonEnemy alien1(0, 5,5,0, 0.5,spriteTest);
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien1.move(player.getX(), player.getY());
    alien1.move(player.getX(), player.getY());
    alien1.move(player.getX(), player.getY());
    ASSERT_EQ(alien.getX(), 3.5);
    ASSERT_EQ(alien.getY(), 3.5);
    ASSERT_EQ(alien1.getX(), 6.5);
    ASSERT_EQ(alien1.getY(), 3.5);
    player.move(200,200);
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien1.move(player.getX(), player.getY());
    alien1.move(player.getX(), player.getY());
    alien1.move(player.getX(), player.getY());
    ASSERT_EQ(alien.getX(), 5);
    ASSERT_EQ(alien.getY(), 5);
    ASSERT_EQ(alien1.getX(), 5);
    ASSERT_EQ(alien1.getY(), 5);
}

TEST(KamikazeEnemy, Attack){
    bool a=false;
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(0,0,0,0,spriteTest);
    KamikazeEnemy alien(10, 35,35,0, 1,spriteTest);
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien.move(player.getX(), player.getY());
    alien.attack(player,a);
    ASSERT_EQ(alien.getHP(), 10);
    alien.move(player.getX(), player.getY());
    alien.attack(player,a);
    ASSERT_EQ(alien.getHP(), 10);
    alien.move(player.getX(), player.getY());
    alien.attack(player,a);
    ASSERT_EQ(alien.getHP(), 0);
}
