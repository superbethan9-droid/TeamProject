#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "DungeonGraph.h"
#include "Inventory.h"

int main()
{
    DungeonGraph dungeon;
    InventoryHashTable inventory;

    Room* currentRoom = dungeon.getRoom("Entrance");

    std::cout << "Dungeon Crawler Milestone 1\n";

    std::string line;

    while (true)
    {
        std::cout << "\n> ";

        if (!std::getline(std::cin, line))
        {
            break;
        }

        std::istringstream input(line);

        std::string command;
        input >> command;

        std::string argument;
        std::getline(input >> std::ws, argument);

        if (command == "quit")
        {
            std::cout << "Goodbye!\n";
            break;
        }

        else if (command == "look")
        {
            std::cout << "\nLocation: "
                      << currentRoom->name
                      << "\n";

            std::cout << currentRoom->description
                      << "\n";

            auto neighbors =
                dungeon.getNeighbors(currentRoom->name);

            std::cout << "\nConnected Rooms:\n";

            for (Room* room : neighbors)
            {
                std::cout << "- "
                          << room->name
                          << "\n";
            }

            if (!currentRoom->items.empty())
            {
                std::cout << "\nItems Here:\n";

                for (const auto& item
                     : currentRoom->items)
                {
                    std::cout << "- "
                              << item
                              << "\n";
                }
            }
        }

        else if (command == "go")
        {
            if (argument.empty())
            {
                std::cout << "Usage: go <room>\n";
                continue;
            }

            if (dungeon.areConnected(
                    currentRoom->name,
                    argument))
            {
                currentRoom =
                    dungeon.getRoom(argument);

                std::cout
                    << "Moved to "
                    << currentRoom->name
                    << "\n";
            }
            else
            {
                std::cout
                    << "That room is not connected.\n";
            }
        }

        else if (command == "take")
        {
            auto it =
                std::find(currentRoom->items.begin(),
                          currentRoom->items.end(),
                          argument);

            if (it ==
                currentRoom->items.end())
            {
                std::cout
                    << "Item not found.\n";
            }
            else
            {
                inventory.insert(
                    argument,
                    "Collected item");

                currentRoom->items.erase(it);

                std::cout
                    << "Picked up "
                    << argument
                    << "\n";
            }
        }

        else if (command == "drop")
        {
            Item* item =
                inventory.lookup(argument);

            if (!item)
            {
                std::cout
                    << "You don't have that item.\n";
            }
            else
            {
                inventory.removeItem(argument);

                currentRoom->items.push_back(argument);

                std::cout
                    << "Dropped "
                    << argument
                    << "\n";
            }
        }

        else if (command == "inventory")
        {
            inventory.displayInventory();
        }

        else if (command == "use")
        {
            Item* item =
                inventory.lookup(argument);

            if (!item)
            {
                std::cout
                    << "You don't have that item.\n";
            }
            else
            {
                std::cout
                    << "Used "
                    << argument
                    << "\n";
            }
        }

        else if (command == "undo")
        {
            std::cout
                << "Undo not implemented yet.\n";
        }

        else
        {
            std::cout
                << "Unknown command.\n";
        }
    }

    return 0;
}
