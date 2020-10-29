#ifndef WORD_H
#define WORD_H

/**
 * A struct to represent a word
 * 
 * For this game, we'll use only 10 letters long words. without spaces inside.
 */
struct Word
{

    #define MAX_SIZE 10

    // letters of the word
    char letters[MAX_SIZE];

    // Discovered letter indexes
    bool discoveredLetters[MAX_SIZE];

    uint8_t length = 0;

    // Constructor
    Word(char word[], uint8_t size)
    {
        for (uint8_t i; i<size; i++) {
            letters[i] = word[i];
            discoveredLetters[i] = false;
        }
        length = size;
    }

    void discoverLetter(uint8_t i)
    {
        discoveredLetters[i] = true;
    }

    void draw(Arduboy2 & arduboy)
    {
        for (uint8_t i=0; i<length; i++) {
            if (discoveredLetters[i]) {
                arduboy.print(letters[i]);
            } else {
                arduboy.print(F("_"));
            }
        }
    }
};

#endif