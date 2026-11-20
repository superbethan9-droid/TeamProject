#ifndef COMBAT_H
#define COMBAT_H

#include <cstdlib>
#include <iostream>
#include "Monster.h"

struct Player
{
    int health = 30;
    int maxHealth = 30;
    int baseDamage = 3;
    bool isAlive() const { return health > 0; }
};

// Random damage from 1..maxDmg
inline int rollDamage(int maxDmg)
{
    return 1 + std::rand() % maxDmg;
}

// One round: player strikes, then monster strikes back if still alive.
inline void combatRound(Player& player, Monster& monster, int weaponBonus)
{
    int dealt = rollDamage(player.baseDamage + weaponBonus);
    monster.health -= dealt;
    std::cout << "You hit the " << monster.name
              << " for " << dealt << " damage.\n";

    if (!monster.isAlive())
    {
        std::cout << "The " << monster.name << " is defeated!\n";
        return;
    }
    
    int taken = rollDamage(monster.attack);
    player.health -= taken;
    std::cout << "The " << monster.name << " hits you for "
              << taken << " damage. (HP: "
              << (player.health > 0 ? player.health : 0)
              << "/" << player.maxHealth << ")\n";
}

#endif

    
