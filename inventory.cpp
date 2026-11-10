#include <iostream>
#include <string>
#include <vector>

// Structure for an item in inventory
struct Item {
    std::string name;
    std::string description;
    int quantity;
    Item* next; // For collision chaining
};

class InventoryHashTable {
private:
    static const int TABLE_SIZE = 101; // Prime number for better distribution
    Item* table[TABLE_SIZE];

    // Simple hash function (djb2 or basic polynomial hash)
    int hashFunction(const std::string& key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % TABLE_SIZE;
    }

public:
    InventoryHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    ~InventoryHashTable() {
        clear();
    }

    // Insert or update an item
    void insert(const std::string& name, const std::string& desc, int qty = 1) {
        int index = hashFunction(name);
        Item* current = table[index];

        // Check if item already exists
        while (current != nullptr) {
            if (current->name == name) {
                current->quantity += qty;
                return;
            }
            current = current->next;
        }

        // Otherwise, insert new item at the head of the chain
        Item* newItem = new Item{name, desc, qty, table[index]};
        table[index] = newItem;
    }

    // Look up an item
    Item* lookup(const std::string& name) {
        int index = hashFunction(name);
        Item* current = table[index];

        while (current != nullptr) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Not found
    }

    // Remove an item (or decrease quantity)
    bool removeItem(const std::string& name, int qty = 1) {
        int index = hashFunction(name);
        Item* current = table[index];
        Item* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                if (current->quantity > qty) {
                    current->quantity -= qty;
                } else {
                    // Remove node from chain
                    if (prev == nullptr) {
                        table[index] = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    delete current;
                }
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; // Item not found
    }

    // Display all items (for the 'inventory' command)
    void displayInventory() {
        std::cout << "\n--- Your Inventory ---\n";
        bool isEmpty = true;
        for (int i = 0; i < TABLE_SIZE; i++) {
            Item* current = table[i];
            while (current != nullptr) {
                std::cout << "- " << current->name << " (x" << current->quantity << "): " << current->description << "\n";
                isEmpty = false;
                current = current->next;
            }
        }
        if (isEmpty) {
            std::cout << "Your inventory is empty.\n";
        }
        std::cout << "----------------------\n";
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Item* current = table[i];
            while (current != nullptr) {
                Item* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }
};
