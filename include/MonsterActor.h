#ifndef MONSTER_ACTOR_H
#define MONSTER_ACTOR_H

#include "Monster.h"
#include <string>

struct MonsterActor {
    Monster monster;
    std::string room;
    int speed;
};

#endif
