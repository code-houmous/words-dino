#ifndef TREASURE_H
#define TREASURE_H

#include "bitmaps.h"

/**
 * A treasure is a box that contains one letter.
 * 
 * Every time you open a box, you discover one letter of the word.
 */
struct Treasure
{

    // State of the box
    enum struct State {
        Opened,
        Closed
    };

    State state = State::Closed;

    // position
    uint8_t x;
    uint8_t y;

    // The index of the letter that it represents in the word
    uint8_t letterIndex;

    void draw(Arduboy2 & arduboy)
    {
        if (state == State::Closed) {
            Sprites::drawOverwrite(x, y, treasureTile, 0);
        }

        Sprites::drawOverwrite(x, y, treasureTile, 1);
    }
};

#endif