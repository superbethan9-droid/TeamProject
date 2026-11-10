#ifndef DUNGEONGRAPH_H
#define DUNGEONGRAPH_H

#include "Room.h"
#include <string>
#include <vector>

class DungeonGraph
{
public:
    DungeonGraph();

    Room* getRoom(const std::string& name);

    bool areConnected(const std::string& roomA,
                      const std::string& roomB);

    std::vector<Room*> getNeighbors(
        const std::string& roomName);

private:
    std::vector<Room> rooms;
    std::vector<std::vector<int>> adjacencyList;

    void addRoom(const std::string& name,
                 const std::string& description);

    void connectRooms(const std::string& roomA,
                      const std::string& roomB);

    int findRoomIndex(const std::string& name);
};

#endif
