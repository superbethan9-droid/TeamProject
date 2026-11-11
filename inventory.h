#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

struct Item {
    std::string name;
    std::string description;
    int quantity;
    Item* next;
};

class InventoryHashTable {
private:
    static const int TABLE_SIZE = 101;
    Item* table[TABLE_SIZE];
    int hashFunction(const std::string& key);

public:
    InventoryHashTable();
    ~InventoryHashTable();

    void insert(const std::string& name, const std::string& desc, int qty = 1);
    Item* lookup(const std::string& name);
    bool removeItem(const std::string& name, int qty = 1);
    void displayInventory();
    void clear();
};

#endif
