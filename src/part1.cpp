#include <iostream>
#include <fstream>
#include <filesystem>
#include "hash.hpp"
#include "word_utils.hpp"
#include "part1.hpp"
#include "config_loader.hpp"

using namespace std;
using json = nlohmann::json;

void part1(){
    json config = loadConfig();
    int tableSize = config.value("table_size", 100000);
    HashTable hashTable(tableSize);

    ifstream file("Book.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file Book.txt" << endl;
        return;
    }

    try {
        processWords(file, hashTable);
    } catch (const exception& e) {
        cerr << "Error processing words: " << e.what() << endl;
    }    
}