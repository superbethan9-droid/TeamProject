#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

struct Room
{
    std::string name;
    std::string description;

    std::vector<std::string> items;
};

#endif
