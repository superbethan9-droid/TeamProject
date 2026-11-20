#include "TurnPriorityQueue.h"
#include <stdexcept>
#include <utility>

bool TurnPriorityQueue::higherPriority(
    const TurnEntry& a, const TurnEntry& b) {

    if (a.speed != b.speed) {
        return a.speed > b.speed;
    }

    if (a.isPlayer != b.isPlayer) {
        return a.isPlayer;
    }

    return a.name < b.name;
}

void TurnPriorityQueue::siftUp(std::size_t index) {
    while (index > 0) {
        std::size_t parent = (index - 1) / 2;

        if (!higherPriority(heap_[index], heap_[parent])) {
            break;
        }

        std::swap(heap_[index], heap_[parent]);
        index = parent;
    }
}

void TurnPriorityQueue::siftDown(std::size_t index) {
    while (true) {
        std::size_t best = index;
        std::size_t left = index * 2 + 1;
        std::size_t right = index * 2 + 2;

        if (left < heap_.size() &&
            higherPriority(heap_[left], heap_[best])) {
            best = left;
        }

        if (right < heap_.size() &&
            higherPriority(heap_[right], heap_[best])) {
            best = right;
        }

        if (best == index) {
            break;
        }

        std::swap(heap_[index], heap_[best]);
        index = best;
    }
}

void TurnPriorityQueue::push(const TurnEntry& entry) {
    heap_.push_back(entry);
    siftUp(heap_.size() - 1);
}

TurnEntry TurnPriorityQueue::pop() {
    if (heap_.empty()) {
        throw std::out_of_range("Turn queue is empty");
    }

    TurnEntry result = heap_.front();

    heap_.front() = heap_.back();
    heap_.pop_back();

    if (!heap_.empty()) {
        siftDown(0);
    }

    return result;
}

const TurnEntry& TurnPriorityQueue::peek() const {
    if (heap_.empty()) {
        throw std::out_of_range("Turn queue is empty");
    }

    return heap_.front();
}

bool TurnPriorityQueue::empty() const {
    return heap_.empty();
}

std::size_t TurnPriorityQueue::size() const {
    return heap_.size();
}
