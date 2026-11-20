#ifndef TURN_PRIORITY_QUEUE_H
#define TURN_PRIORITY_QUEUE_H

#include <cstddef>
#include <string>
#include <vector>

struct TurnEntry {
    std::string name;
    int speed;
    bool isPlayer;
};

class TurnPriorityQueue {
public:
    void push(const TurnEntry& entry);
    TurnEntry pop();
    const TurnEntry& peek() const;
    bool empty() const;
    std::size_t size() const;

private:
    std::vector<TurnEntry> heap_;

    static bool higherPriority(const TurnEntry& a,
                               const TurnEntry& b);

    void siftUp(std::size_t index);
    void siftDown(std::size_t index);
};

#endif
