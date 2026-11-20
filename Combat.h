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
