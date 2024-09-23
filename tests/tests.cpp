#include <iostream>
#include <cassert>
#include "hash.hpp"
#include "word_utils.hpp"

void testInsertAndGet() {
    HashTable hashTable(100); // Specify table size
    hashTable.insert("hello", 1);
    hashTable.insert("world", 2);
    assert(hashTable.get("hello").value() == 1);
    assert(hashTable.get("world").value() == 2);
    std::cout << "testInsertAndGet passed!" << std::endl;
}

void testUpdateValue() {
    HashTable hashTable(100); // Specify table size
    hashTable.insert("hello", 1);
    hashTable.insert("hello", 3);
    assert(hashTable.get("hello").value() == 3);
    std::cout << "testUpdateValue passed!" << std::endl;
}

void testRemove() {
    HashTable hashTable(100); // Specify table size
    hashTable.insert("hello", 1);
    hashTable.remove("hello");
    assert(!hashTable.get("hello").has_value());
    std::cout << "testRemove passed!" << std::endl;
}

void testGetFirstAndLast() {
    HashTable hashTable(100); // Specify table size
    hashTable.insert("first", 1);
    hashTable.insert("second", 2);
    hashTable.insert("third", 3);
    assert(hashTable.get_first().value().first == "first");
    assert(hashTable.get_last().value().first == "third");
    std::cout << "testGetFirstAndLast passed!" << std::endl;
}

void testCleanWord() {
    std::string word1 = "Hello!";
    cleanWord(word1);
    assert(word1 == "hello");

    std::string word2 = "Gutenberg-tm";
    cleanWord(word2);
    assert(word2 == "gutenberg-tm");

    std::string word3 = "test - clean";
    cleanWord(word3);
    assert(word3 == "testclean");

    std::cout << "testCleanWord passed!" << std::endl;
}

int main() {
    testInsertAndGet();
    testUpdateValue();
    testRemove();
    testGetFirstAndLast();
    testCleanWord();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}