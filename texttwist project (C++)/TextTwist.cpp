// File name: TextTwist.cpp
// Description: implements the TextTwister class


#include "algorithm"
#include "iostream"
#include "fstream"
#include "TextTwist.h"


const int LETTERS = 7;
const int WORD_LEN = 3;

//Class constructor
TextTwist::TextTwist() : visitedWords(), dictionary(), visitedPrefix() {}

//run
//plays the game
// pre: someone has called  the method in the main
// post: the game is run
void TextTwist::run() {

    std::cout << "Loading valid words. Please wait..." << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Welcome to the TEXT TWIST Solver." << std::endl;
    std::cout << std::endl << std::endl;
    //builds lexicon of acceptable words.
    dictionary.loadFromFile("ospd.txt");

    //prompt user and read in input
    std::string s = userInput();

    generator(s, "");

    // print words
    visitedWords.print();


}

// generator
// The lexicon will be loaded from the file "ospd.txt"
// pre: checks that it is an acceptable word
// post: lexicon of acceptable words is built
void TextTwist::generator(std::string s, std::string word) {

    if (!visitedWords.isWord(word) && dictionary.isWord(word) && word.length() >= WORD_LEN) {
        visitedWords.insert(word); //store in lexicon
    }

    //backtracking
    for (size_t i = 0; i < s.length(); i++) {
        char charToAdd = s[i];
        word += charToAdd;

        s = s.erase(i, 1);

        //recursive
        if (dictionary.isPrefix(word) && !visitedWords.isWord(word) &&
            !visitedPrefix.isWord(word)) {
            visitedPrefix.insert(word);
            generator(s, word);
        }

        //going back
        word = word.substr(0, word.length() - 1); //check if doing this right
        s.insert(i, 1, charToAdd);
    }
}

// userInput
// prompt user and read in input
// pre: the user enters the seven letters of the Text Twist game and
// post:  characters are read in from the terminal.
std::string TextTwist::userInput() {
    bool correct = false;
    std::string str = "";
    while (!correct) {
        std::cout << "Enter the " << LETTERS << " letters of the Text Twist game: ";
        std::cin >> str;
        if (str.length() != LETTERS) {
            std::cout << "You must enter exactly " << LETTERS << " characters" << std::endl;
        } else if (std::all_of(str.begin(), str.end(), [](char i) { return islower(i); })) {
            correct = true;
        } else {
            std::cout << "You must enter only lowercase characters" << std::endl;
        }
    }
    return str;
}

