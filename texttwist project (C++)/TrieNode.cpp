// File name: trienode.cpp
// Description: implements a helper method for trie.h

#include <cstddef>
#include <stdexcept>
#include "iostream"
#include <string>
#include "TrieNode.h"

//  Constructor
// post: Takes a character for the node, and a bool
// indicating whether it represents the end of a word. Note, there is no default ctor.
TrieNode::TrieNode(char c, bool b) : character(c), end(b) {
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        array[i] = nullptr;
    }

}

// Copy Constructor
// pre: parameter object, rhs, exists
// post:  is created to be a copy of the parameter
TrieNode::TrieNode(const TrieNode &rhs) : character(rhs.character), end(rhs.end) {
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        if (rhs.array[i] != nullptr) {
            array[i] = new TrieNode(*rhs.array[i]);
        } else {
            array[i] = nullptr;
        }
    }

}

// Class Deconstructor
// pre: it exists
// post: is destroyed and any dynamic memory is returned to the system
TrieNode::~TrieNode() {
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        delete array[i];
    }


}

// Assignment operator
// Assigns a one to another
// pre: both class objects exist
// post: this class object gets assigned a copy of the parameter class object
const TrieNode &TrieNode::operator=(const TrieNode &rhs) {

    if (this != &rhs) {
        TrieNode temp(rhs); //call copy constructor to make a temp
        std::swap(this->character, temp.character);
        std::swap(this->end, temp.end);
        std::swap(this->array, temp.array);

    }
    return *this;

}

// insert
// Inserts word into the TrieNode
// pre: checks if is an empty string
// post: Insert str starting with the given TrieNode. Create new TrieNodes
// as needed and be sure to set the boolean flag on the last node to true.
void TrieNode::insert(const std::string &str) {
    if (str.empty()) {
        end = true;
    } else if (array[str[0] - 'a'] != nullptr) {
        array[str[0] - 'a']->insert(str.substr(1));

    } else if (!isalpha(str[0])) {
        std::cout << "user did not enter valid string" << std::endl;
    } else {
        array[str[0] - 'a'] = new TrieNode(str[0], false);
        array[str[0] - 'a']->insert(str.substr(1));
    }

}

// isWord
//  Returns true if str is in the sub-Trie starting at the given TrieNode,
// else ret                                                                                                                                                                                                             urns false
// pre: check whether it is an empty string or the end of a word
// post: the user knows if it is a word within the tree
bool TrieNode::isWord(const std::string &str) const {
    if (str.empty() && end) {
        return true;
    } else if (str.empty()) {
        return end;
    } else if (array[str[0] - 'a'] != nullptr) { //making sure it is there
        return array[str[0] - 'a']->isWord(str.substr(1));
    } else {
        return false;
    }

}


// isPrefix
// Returns true if pre is a prefix of a word in the sub-Trie starting at
// the given TrieNode, else returns false
// pre: checks if it is an empty string
// post: the user knows whether or nots it is a prefix of a word
bool TrieNode::isPrefix(const std::string &pre) const {

    if (pre.empty()) {
        return true;
    } else if (array[pre[0] - 'a'] != nullptr) { //making sure it is there
        return array[pre[0] - 'a']->isPrefix(pre.substr(1));
    } else {
        return false;
    }

}

// print
// Prints all words starting at the given TrieNode. The parameter
// string str stores the letters of all previous TrieNode objects up to
// the node currently being processed.
// pre: checks if the word is at the end
// post: the words are printed
void TrieNode::print(const std::string &str) const {

    std::string newStr = str;
    if (character != ' ') {
        newStr += character;
    }
    if (end) {
        std::cout << newStr << std::endl;
    }


    for (size_t i = 0; i < NUM_LETTERS; i++) {
        if (array[i] != nullptr) {
            array[i]->print(newStr);
        }
    }
}

// size
//Returns a count all the nodes in the sub-Trie that end a word
// post: Returns size from the private section of class.
size_t TrieNode::wordCount() const {
    size_t count = 0;
    if (end) {
        count++;
    }
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        if (array[i] != nullptr) {
            count += array[i]->wordCount();
        }
    }
    return count;
}


