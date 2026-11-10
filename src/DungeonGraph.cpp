#include "DungeonGraph.h"

DungeonGraph::DungeonGraph()
{
    addRoom("Entrance",
            "You stand at the entrance of the dungeon.");

    addRoom("Great Hall",
            "A large hall with towering ceilings.");

    addRoom("Armory",
            "Racks of old weapons line the walls.");

    addRoom("Barracks",
            "Former quarters for soldiers.");

    addRoom("Courtyard",
            "An open courtyard surrounded by stone.");

    addRoom("Library",
            "Dusty shelves filled with ancient books.");

    addRoom("Kitchen",
            "Old cooking equipment fills the room.");

    addRoom("Cellar",
            "A damp cellar with a musty smell.");

    addRoom("Tower",
            "A tall tower overlooking the dungeon.");

    addRoom("Crypt",
            "Dark tombs line the walls.");

    addRoom("Vault",
            "A heavily reinforced treasure vault.");

    addRoom("Exit",
            "The way out of the dungeon.");

    connectRooms("Entrance", "Great Hall");
    connectRooms("Entrance", "Armory");

    connectRooms("Armory", "Barracks");

    connectRooms("Barracks", "Courtyard");

    connectRooms("Great Hall", "Courtyard");
    connectRooms("Great Hall", "Library");
    connectRooms("Great Hall", "Kitchen");

    connectRooms("Library", "Tower");

    connectRooms("Kitchen", "Cellar");

    connectRooms("Cellar", "Crypt");

    connectRooms("Tower", "Vault");

    connectRooms("Courtyard", "Vault");

    connectRooms("Crypt", "Vault");

    connectRooms("Vault", "Exit");
}

void DungeonGraph::addRoom(const std::string& name,
                           const std::string& description)
{
    Room room;

    room.name = name;
    room.description = description;

    rooms.push_back(room);

    adjacencyList.push_back(std::vector<int>());
}

int DungeonGraph::findRoomIndex(const std::string& name)
{
    for (size_t i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].name == name)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void DungeonGraph::connectRooms(const std::string& roomA,
                                const std::string& roomB)
{
    int indexA = findRoomIndex(roomA);
    int indexB = findRoomIndex(roomB);

    if (indexA == -1 || indexB == -1)
    {
        return;
    }

    adjacencyList[indexA].push_back(indexB);
    adjacencyList[indexB].push_back(indexA);
}

Room* DungeonGraph::getRoom(const std::string& name)
{
    int index = findRoomIndex(name);

    if (index == -1)
    {
        return nullptr;
    }

    return &rooms[index];
}

bool DungeonGraph::areConnected(const std::string& roomA,
                                const std::string& roomB)
{
    int indexA = findRoomIndex(roomA);
    int indexB = findRoomIndex(roomB);

    if (indexA == -1 || indexB == -1)
    {
        return false;
    }

    for (int neighbor : adjacencyList[indexA])
    {
        if (neighbor == indexB)
        {
            return true;
        }
    }

    return false;
}

std::vector<Room*> DungeonGraph::getNeighbors(
    const std::string& roomName)
{
    std::vector<Room*> neighbors;

    int index = findRoomIndex(roomName);

    if (index == -1)
    {
        return neighbors;
    }

    for (int neighborIndex : adjacencyList[index])
    {
        neighbors.push_back(&rooms[neighborIndex]);
    }

    return neighbors;
}
