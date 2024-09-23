#include "hash.hpp"
#include <iostream>
#include <optional>
#include <functional>

HashTable::HashTable(int tableSize) : table(tableSize), currentSize(0), firstIndex(-1), lastIndex(-1) {}

int HashTable::hashFunction(const string &key) {
    std::hash<string> hash_fn;
    return hash_fn(key) % tableSize;
}

void HashTable::insert(const string &key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % tableSize;
        if (index == originalIndex) {
            std::cerr << "HashTable is full!" << std::endl;
            return;
        }
    }

    if (!table[index].isActive) {
        currentSize++;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].isActive = true;

    if (firstIndex == -1) {
        firstIndex = index;
    }
    lastIndex = index;
}

void HashTable::remove(const string &key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            return; // Key not found
        }
    }

    if (table[index].isActive) {
        table[index].isActive = false;
        currentSize--;
    }
}

std::optional<int> HashTable::get(const string &key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            return std::nullopt; // Key not found
        }
    }

    if (table[index].isActive) {
        return table[index].value;
    }

    return std::nullopt;
}

std::optional<pair<string, int>> HashTable::get_last() {
    if (lastIndex != -1 && table[lastIndex].isActive) {
        return std::make_pair(table[lastIndex].key, table[lastIndex].value);
    }
    return nullopt;
}

std::optional<pair<string, int>> HashTable::get_first() {
    if (firstIndex != -1 && table[firstIndex].isActive) {
        return std::make_pair(table[firstIndex].key, table[firstIndex].value);
    }
    return std::nullopt;
}