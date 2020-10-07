// File name: TextTwist.h
// Description: prints out possible words given an input of letters

#include "Trie.h"
#include "stdexcept"
#include "string"

#ifndef PROJECT10_TEXTTWIST_H
#define PROJECT10_TEXTTWIST_H

class TextTwist {
private:
    Trie visitedWords;
    Trie dictionary;
    Trie visitedPrefix;


    // generator
    // The lexicon will be loaded from the file "ospd.txt"
    // pre: checks that it is an acceptable word
    // post: lexicon of acceptable words is built
    void generator(std::string s, std::string word);


    // userInput
    // prompt user and read in input
    // pre: the user enters the seven letters of the Text Twist game and
    // post:  characters are read in from the terminal.
    std::string userInput();


public:

    //Class constructor
    TextTwist();

    //run
    //plays the game
    // pre: someone has called  the method in the main
    // post: the game is run
    void run();

};

#endif //PROJECT10_TEXTTWIST_H
