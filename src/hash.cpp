#include "hash.hpp"

HashTable::HashTable() : table(TABLE_SIZE), currentSize(0), firstIndex(-1), lastIndex(-1) {}

int HashTable::hashFunction(const string &key) {
    hash<string> hash_fn;
    return hash_fn(key) % TABLE_SIZE;
}

void HashTable::insert(const string &key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;
    bool found = false;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            cerr << "HashTable is full!" << endl;
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
            return nullopt; // Key not found
        }
    }

    if (table[index].isActive) {
        return table[index].value;
    }

    return nullopt;
}

std::optional<pair<string, int>> HashTable::get_last() {
    if (lastIndex != -1 && table[lastIndex].isActive) {
        return make_pair(table[lastIndex].key, table[lastIndex].value);
    }
    return nullopt;
}

std::optional<pair<string, int>> HashTable::get_first() {
    if (firstIndex != -1 && table[firstIndex].isActive) {
        return make_pair(table[firstIndex].key, table[firstIndex].value);
    }
    return nullopt;
}