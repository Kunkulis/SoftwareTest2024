#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace std;

struct HashNode {
    string key;
    int value;
    bool isActive; // To mark active/inactive nodes for linear probing
    HashNode() : key(""), value(0), isActive(false) {}
};

class HashTable {
private:
    vector<HashNode> table;
    int tableSize;
    int currentSize;
    int firstIndex;
    int lastIndex;

    int hashFunction(const string &key);

public:
    HashTable(int tableSize);
    void insert(const string &key, int value);
    void remove(const string &key);
    std::optional<int> get(const string &key);
    std::optional<pair<string, int>> get_last();
    std::optional<pair<string, int>> get_first();
};

#endif