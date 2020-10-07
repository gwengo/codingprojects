// Author: Gwen!
// Description: is a helper method for trie.h


#ifndef PROJECT10_TRIENODE_H
#define PROJECT10_TRIENODE_H

#include <cstddef>
#include <string>

const int NUM_LETTERS = 26;

class TrieNode {
private:

    typedef TrieNode *pointers;
    pointers array[NUM_LETTERS];
    char character;
    bool end;


public:

    //  Constructor
    // post: Takes a character for the node, and a bool
    // indicating whether it represents the end of a word. Note, there is no default ctor.
    TrieNode(char c, bool b);

    // Copy Constructor
    // pre: parameter object, rhs, exists
    // post:  is created to be a copy of the parameter
    TrieNode(const TrieNode &rhs);

    // Class Deconstructor
    // pre: it exists
    // post:  is destroyed and any dynamic memory is returned to the system
    ~TrieNode();

    // Assignment operator
    // Assigns a oneto another
    // pre: both class objects exist
    // post: this class object gets assigned a copy of the parameter class object
    const TrieNode &operator=(const TrieNode &rhs);

    // insert
    // Inserts word into the TrieNode
    // pre: checks if is an empty string
    // post: Insert str starting with the given TrieNode. Create new TrieNodes
    // as needed and be sure to set the boolean flag on the last node to true.
    void insert(const std::string &str);

    // isWord
    //  Returns true if str is in the sub-Trie starting at the given TrieNode,
    // else ret                                                                                                                                                                                                             urns false
    // pre: check whether it is an empty string or the end of a word
    // post: the user knows if it is a word within the tree
    bool isWord(const std::string &str) const;


    // isPrefix
    // Returns true if pre is a prefix of a word in the sub-Trie starting at
    // the given TrieNode, else returns false
    // pre: checks if it is an empty string
    // post: the user knows whether or nots it is a prefix of a word
    bool isPrefix(const std::string &pre) const;

    // print
    // Prints all words starting at the given TrieNode. The parameter
    // string str stores the letters of all previous TrieNode objects up to
    // the node currently being processed.
    // pre: checks if the word is at the end
    // post: the words are printed
    void print(const std::string &str) const;

    // WordCount
    //Returns a count all the nodes in the sub-Trie that end a word
    // post: Returns size from the private section of class.
    size_t wordCount() const;

};


#endif //PROJECT10_TRIENODE_H
