// File name: trie.cpp
// Description: creates / uses a tree-like ADT to store words.

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include <algorithm>


// default Constructor
// post: it is created & initialized to be empty
Trie::Trie() : myRoot(' ', false) {
}


// insert
// Inserts word into the Trie
// pre: trieNode tests for all edge conditions
// post: the word is inserted into the Trie
void Trie::insert(const std::string &word) {
    std::string wordTwo = word;
    std::transform(wordTwo.begin(), wordTwo.end(), wordTwo.begin(), ::tolower);
    myRoot.insert(wordTwo);
}

// loadFromFile
// Insert all words in the specified file into the Trie. Throws a
// std::invalid_argument exception if the specified file cannot be opened.
// pre: we check the the file can be opened
// post: the words have been inserted into the trie
void Trie::loadFromFile(const std::string &filename) {

    std::ifstream infile(filename.c_str());
    if (!infile) {    //verify file was opened successfully
        throw std::invalid_argument("specified file cannot be opened");
    }

    //read all the words from the file
    std::string str;
    while (infile >> str) {
        insert(str);
    } //done processing the file


    //close the file
    infile.close();
}

// isWord
// Returns true if word is in the Trie, else returns false
// pre: trieNode tests for all edge conditions
// post: we know if it is a word in the trie or not
bool Trie::isWord(const std::string &word) const {
    return myRoot.isWord(word);
}


// isPrefix
// Returns true if pre is a prefix of a word in the Trie, else returns false
// pre: trieNode tests for all edge conditions
// post: we find out if it is a prefix or not
bool Trie::isPrefix(const std::string &pre) const {
    return myRoot.isPrefix(pre);
}

// print
// Print all words in the Trie, one per line. Print in alphabetical order.
// pre: trieNode tests for all edge conditions
// post: all words are printed
void Trie::print() const {
    myRoot.print("");
}

// size
// Returns a count all the words in the Trie
//pre: trieNode tests for all edge conditions
// post: Returns size from the private section of class.
size_t Trie::wordCount() const {
    return myRoot.wordCount();
}
