#include "inventory.h"
#include <iostream>

int InventoryHashTable::hashFunction(const std::string& key)
{
    unsigned long hash = 5381;

    for (char c : key)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

InventoryHashTable::InventoryHashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = nullptr;
    }
}

InventoryHashTable::~InventoryHashTable()
{
    clear();
}

void InventoryHashTable::insert(const std::string& name,
                                const std::string& desc,
                                int qty)
{
    int index = hashFunction(name);

    Item* current = table[index];

    while (current != nullptr)
    {
        if (current->name == name)
        {
            current->quantity += qty;
            return;
        }

        current = current->next;
    }

    Item* newItem = new Item{
        name,
        desc,
        qty,
        table[index]
    };

    table[index] = newItem;
}

Item* InventoryHashTable::lookup(const std::string& name)
{
    int index = hashFunction(name);

    Item* current = table[index];

    while (current != nullptr)
    {
        if (current->name == name)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool InventoryHashTable::removeItem(const std::string& name,
                                    int qty)
{
    int index = hashFunction(name);

    Item* current = table[index];
    Item* previous = nullptr;

    while (current != nullptr)
    {
        if (current->name == name)
        {
            if (current->quantity > qty)
            {
                current->quantity -= qty;
            }
            else
            {
                if (previous == nullptr)
                {
                    table[index] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                delete current;
            }

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

void InventoryHashTable::displayInventory()
{
    std::cout << "\n--- Inventory ---\n";

    bool empty = true;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Item* current = table[i];

        while (current != nullptr)
        {
            std::cout << current->name
                      << " x"
                      << current->quantity
                      << " - "
                      << current->description
                      << '\n';

            empty = false;
            current = current->next;
        }
    }

    if (empty)
    {
        std::cout << "Inventory is empty.\n";
    }

    std::cout << "-----------------\n";
}

void InventoryHashTable::clear()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Item* current = table[i];

        while (current != nullptr)
        {
            Item* temp = current;
            current = current->next;
            delete temp;
        }

        table[i] = nullptr;
    }
}
