// File name: trie.h
// Description: creates / uses a tree-like ADT to store words.


#ifndef PROJECT10_TRIE_H
#define PROJECT10_TRIE_H

#include <cstddef>
#include "TrieNode.h"
#include <stdexcept>

typedef std::string ItemType; //  currently holds strings

class Trie {

private:

    TrieNode myRoot;

public:


    // default Constructor
    // post: it is created & initialized to be empty
    Trie();

    // insert
    // Inserts word into the Trie
    // pre: trieNode tests for all edge conditions
    // post: the word is inserted into the Trie
    void insert(const std::string &word);

    // loadFromFile
    // Insert all words in the specified file into the Trie. Throws a
    // std::invalid_argument exception if the specified file cannot be opened.
    // pre: we check the the file can be opened
    // post: the words have been inserted into the trie
    void loadFromFile(const std::string &filename);

    // isWord
    // Returns true if word is in the Trie, else returns false
    // pre: trieNode tests for all edge conditions
    // post: we know if it is a word in the trie or not
    bool isWord(const std::string &word) const;


    // isPrefix
    // Returns true if pre is a prefix of a word in the Trie, else returns false
    // pre: trieNode tests for all edge conditions
    // post: we find out if it is a prefix or not
    bool isPrefix(const std::string &pre) const;

    // print
    // Print all words in the Trie, one per line. Print in alphabetical order.
    // pre: trieNode tests for all edge conditions
    // post: all words are printed
    void print() const;

    // wordCount
    // Returns a count all the words in the Trie
    // pre: trieNode tests for all edge conditions
    // post: Returns size from the private section of class.
    size_t wordCount() const;
};


#endif //PROJECT10_TRIE_H

