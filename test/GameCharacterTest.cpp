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
    GameCharacter player(8, 10);
    Weapon gun(10, 5, 0, 0);
    player.EquipWeapon(6, &gun);
    ASSERT_EQ(10, player.weapon->power);
}

TEST(GameCharacter, ReceivedDamage) {
    int hp;
    GameCharacter player(5, 10);
    KamikazeEnemy alien(1, 0);
    player.ReceiveDamage(alien.Attack(0, 0));
    hp = player.getGameCharacterHP();
    ASSERT_EQ(10, hp);
}

