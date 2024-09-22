#include <iostream>
#include <fstream>
#include <filesystem>
#include "hash.hpp"
#include "word_utils.hpp"
#include "part1.hpp"

using namespace std;

void part1(){
    HashTable hashTable;

    cout << "Current working directory: " << filesystem::current_path() << endl;

    ifstream file("Book.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file Book.txt" << endl;
        return;
    }

    processWords(file, hashTable);    
}