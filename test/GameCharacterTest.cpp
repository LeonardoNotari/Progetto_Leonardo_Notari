//
// Created by leonardo on 01/07/20.
//
#include <gtest/gtest.h>
#include "../GameCharacter.h"
#include "../Weapon.h"
#include "../KamikazeEnemy.h"

TEST(GameCharacter, IsPossibleEquipWeapon) {
    GameCharacter player(5, 10);
    ASSERT_TRUE(player.IsPossibleEquipWeapon(5));
}

TEST(GameCharacter, EquipWeapon) {
    Weapon*weapon;
    GameCharacter player(8, 10);
    Weapon gun(9, 5, 0, 0);
    player.EquipWeapon(6, &gun);
    weapon=player.getWeapon();
    ASSERT_EQ(9, weapon->power);
}

TEST(GameCharacter, ReceivedDamage) {
    int hp;
    GameCharacter player(0, 10);
    KamikazeEnemy alien(1, 0,9);
    player.ReceiveDamage(alien.Attack(1, 0));
    hp = player.getGameCharacterHP();
    ASSERT_EQ(1, hp);
}

