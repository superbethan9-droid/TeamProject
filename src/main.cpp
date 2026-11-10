#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::cout << "Dungeon Crawler Milestone 1\n";
  std::cout << "Commands: look, go <room>, take <item>, drop <item>, inventory, use <item>, undo, quit\n";
  std::string line;

  while (true) {
    std::cout << "\n> ";
    if (!std::getline(std::cin, line)) {
      break;
    }

    std::istringstream input(line);
    std::string command;
    input >> command;

    if (command.empty()) {
      continue;
    }

    std::string argument;
    std::getline(input >> std::ws, argument);

    if (command == "quit") {
      std::cout << "GOODBYE! Final score table will be added later\n";
      break;

    }
    else if (command == "look") {
      std::cout << "look recognized (room details not connected yet)\n";
    }
    else if (command == "inventory") {
      std::cout << "inventory recognized (hashtable not connected yet)\n";
    }
    else if (command == "undo") {
      std::cout << "undo recogized (stack not connected yet)\n";
    }
    else if (command =="go" ||
	     command == "take" ||
	     command == "drop" ||
	     command == "use") {
      if (argument.empty()) {
	std::cout << "Usage: " << command
		  << " <"
		  << (command == "go" ? "room" : "item")
		  << ">\n";
      }
      else {
	std::cout << command << " '"
		  << argument
		  << "' recognized (gameplay not connected yet)\n";
      }
    }
    else {
      std::cout << "Unknown command. try look, go, take, drop, inventory, use, undo, or quit\n";
    }
  }
  return 0;
}
