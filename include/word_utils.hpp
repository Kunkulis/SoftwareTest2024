#ifndef WORD_UTILS_HPP
#define WORD_UTILS_HPP

#include <string>
#include <fstream>
#include "hash.hpp"

void cleanWord(std::string &word);
void processWords(std::ifstream &file, HashTable &hashTable);

#endif