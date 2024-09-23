#include "word_utils.hpp"
#include <cctype>
#include <sstream>
#include <iostream>

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
    word.resize(j);
}

void processWords(ifstream &file, HashTable &hashTable) {
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string word;
        while (ss >> word) {
            cleanWord(word);
            if (!word.empty()) {
                // Get the current count of the word
                auto currentCountOpt = hashTable.get(word);
                int currentCount = currentCountOpt.value_or(0);
                // Insert the word with the updated count
                hashTable.insert(word, currentCount + 1);
            }
        }
    }
}