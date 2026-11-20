#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "DungeonGraph.h"
#include "inventory.h"

#include "Combat.h"
#include "MonsterActor.h"
#include "TurnPriorityQueue.h"

int main()
{
    DungeonGraph dungeon;
    InventoryHashTable inventory;
    
    Player player;
    std::vector<MonsterActor> monsters = {
        {{"Rat King", "A giant rat", 10, 10, 2, ""},
	 "Cellar", 4},

        {{"Goblin", "A hostile goblin", 15, 15, 3, ""},
         "Barracks", 6},

        {{"Guard", "An armored guard", 25, 25, 4, ""},
         "Courtyard", 5},

        {{"Skeleton", "An undead skeleton", 20, 20, 2, ""},
         "Crypt", 3}
    };


    Room* currentRoom = dungeon.getRoom("Entrance");

    std::cout << "====================================\n";
    std::cout << "      DUNGEON CRAWLER\n";
    std::cout << "====================================\n";
    std::cout << "Available Commands:\n";
    std::cout << "  look              - Examine room\n";
    std::cout << "  go <room>         - Move to room\n";
    std::cout << "  take <item>       - Pick up item\n";
    std::cout << "  drop <item>       - Drop item\n";
    std::cout << "  inventory         - View inventory\n";
    std::cout << "  use <item>        - Use an item\n";
    std::cout << "  undo              - Undo last action\n";
    std::cout << "  menu              - Show commands\n";
    std::cout << "  quit              - Exit game\n";
    std::cout << "====================================\n";

    std::string line;

    bool gameRunning = true;

    while (gameRunning && player.isAlive())
    {
      TurnPriorityQueue turnOrder;
      turnOrder.push({"Player", 5, true});

      for (const MonsterActor& actor : monsters)
      {
        if (actor.monster.isAlive())
        {
            turnOrder.push({
                actor.monster.name,
                actor.speed,
                false
            });
        }
      }

      while (!turnOrder.empty() &&
           gameRunning &&
           player.isAlive())
      {
        TurnEntry turn = turnOrder.pop();

        
	if (!turn.isPlayer)
	{
	  for (MonsterActor& actor : monsters)
	  {
	    if (actor.monster.name == turn.name &&
		actor.monster.isAlive())
	    {
	      if (actor.room == currentRoom->name)
              {
                std::cout << "\nEncounter: "
                          << actor.monster.name << "!\n";

                int weaponBonus =
                    inventory.lookup("Sword") ? 3 : 0;

                combatRound(player, actor.monster,
                            weaponBonus);

                if (!player.isAlive())
		  {
		    std::cout << "Game Over! "
                              << "You were defeated.\n";
                    gameRunning = false;
                }
              }
              else
              {
                std::cout << "[Turn] "
                          << actor.monster.name
                          << " is in " << actor.room
                          << " (movement not connected yet).\n";
              }
	      break;
	    }
	  }
	  continue;
	}

     
        std::cout << "\n> ";

        if (!std::getline(std::cin, line))
        {
            gameRunning = false;
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
	    gameRunning=false;
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
		if (currentRoom->name == "Exit")
		  {
		    if (inventory.lookup("Treasure") != nullptr)
		      {
			std::cout << "\nCongratulations! You escaped "
                                  << "the dungeon with the Treasure!\n";
			std::cout << "YOU WIN!\n";
			gameRunning = false;
		      }
		      else
		      {
			std::cout << "You need the treasure to escape the dungeon!\n";
		      }
		  }
			
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
	  std::cout << "Unknown command.\n";
        }
      }
    }
    return 0;
}
