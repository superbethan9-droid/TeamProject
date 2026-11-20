#ifndef MONSTER_H
#define MONSTER_H

#include <string>

struct Monster
{
    std::string name;
    std::string description;
    int health;
    int maxHealth;
    int attack;      // max damage per hit
    std::string drop; // item left behind when defeated ("" for none)

    bool isAlive() const { return health > 0; }
};

#endif
