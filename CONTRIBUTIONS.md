Dungeon crawler contributions

All these contributions will be updated as we go along
 
Paige -
      Created inventory.h and inventory.cpp
      Implemented a custom inventory hash table using separate chaining for collision handling
      Created an Item structure containing item names, descriptions, quantities, and linked-list	pointers
      Implemented a hash function for storing items in the hash table
      Implemented item insertion and quantity updates
      Implemented item lookup by name
      Implemented item removal and quantity reduction
      Implemented functionality to display the player's inventory
      Added memory cleanup functionality using a destructor and clear()

Jacob -
      Created DungeonGraph.h and DungeonGraph.cpp
      Created the Room.h structure
      Implemented the dungeon rooms and their connections
      Implemented room lookup using getRoom()
      Implemented room connection checking using areConnected()
      Implemented neighboring room retrieval using getNeighbors()
      Created the dungeon's adjacency list representation

Ethan -
      Created the initial README.md documenting the project and team members
      Created the Makefile for compiling and running the project
      Implemented the basic command loop in main.cpp
      Added command recognition for look, go, take, drop, inventory, use, undo, and quit
      Added support for commands containing room and item names
      Successfully compiled and tested the basic command loop

