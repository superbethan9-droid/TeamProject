#include "TurnPriorityQueue.h"
#include <cassert>
#include <iostream>
#include <string>

int main() {
    TurnPriorityQueue queue;
    assert(queue.empty());
    queue.push({"Skeleton", 3, false});
    queue.push({"Guard", 5, false});
    queue.push({"Player", 5, true});
    queue.push({"Rat King", 4, false});
    queue.push({"Goblin", 6, false});
    assert(queue.size() == 5);
    assert(queue.peek().name == "Goblin");
    const std::string expected[] = {
        "Goblin",
        "Player",
        "Guard",
        "Rat King",
        "Skeleton"
    };
    for (const std::string& name : expected) {
        assert(queue.pop().name == name);
    }
    assert(queue.empty());
    std::cout << "PASS: Priority queue turn order\n";
    return 0;
}
