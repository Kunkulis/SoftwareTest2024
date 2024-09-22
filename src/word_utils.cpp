#include "word_utils.hpp"
#include <cctype>
#include <sstream>

void cleanWord(std::string &word) {
    size_t j = 0;
    bool lastWasAlpha = false;
    for (size_t i = 0; i < word.size(); ++i) {
        if (isalpha(word[i])) {
            word[j++] = tolower(word[i]);
            lastWasAlpha = true;
        } else if (word[i] == '-' && lastWasAlpha && i + 1 < word.size() && isalpha(word[i + 1])) {
            word[j++] = word[i];
            lastWasAlpha = false;
        } else {
            lastWasAlpha = false;
        }
    }
    word.resize(j);  // Resize the string to the new length
}

void processWords(ifstream &file, HashTable &hashTable) {
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string word;
        while (ss >> word) {
            cleanWord(word);
            if (!word.empty()) {
                int currentCount = 0;
                // If the word is already in the hash table, increment its count
                if (hashTable.get(word).has_value()) {
                    currentCount = hashTable.get(word).value();
                    hashTable.insert(word, currentCount + 1);
                }
                // If it's a new word, insert it with a count of 1
                else {
                    hashTable.insert(word, 1);
                }
            }
        }
    }
}