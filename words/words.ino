#include <Arduboy2.h>

#include "src/Dinosaur.h"
#include "src/MapGenerator.h"
#include "src/Word.h"

Arduboy2 arduboy;
Dinausor dinausor;
MapGenerator mapGenerator;

Word words[10] = {
    Word("CIEL", 4),
    Word("OUPS", 4),
    Word("NINJAGO", 7),
    Word("ALLO", 4),
    Word("BALLON", 6),
    Word("DINOSAURE", 9),
    Word("CHOCOLAT", 8),
    Word("BONHOMME", 8),
    Word("PAPRIKA", 7),
    Word("FRAISE", 6)
};

enum struct Screen {
    Map,
    Letters
};

Screen screen = Screen::Map;

uint8_t currentWordIndex = 10;

uint8_t lastDiscoveredLetterIndex = 0;

// True when the game needs to regenerate the map and the word
bool reload = true;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
    // initiate arduboy instance
    arduboy.begin();

    // here we set the framerate to 15, we do not need to run at
    // default 60 and it saves us battery life
    arduboy.setFrameRate(15);

    arduboy.initRandomSeed();

    dinausor.movable.x = 16;
    dinausor.movable.y = 16;

    shuffleWords();
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
    // pause render until it's time for the next frame
    if (!(arduboy.nextFrame()))
        return;

    if (reload) {
        arduboy.initRandomSeed();
        screen = Screen::Map;

        currentWordIndex++;
        if (currentWordIndex > 10) {
            currentWordIndex = 0;
        }

        lastDiscoveredLetterIndex = 0;

        mapGenerator.newMap();
        mapGenerator.putTreasuresRandomly(words[currentWordIndex]);

        reload = false;
        return;
    }

    // first we clear our screen to black
    arduboy.clear();

    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON)) {
        if (screen == Screen::Letters) {
            screen = Screen::Map;
        } else {
            screen = Screen::Letters;
        }

        if (lastDiscoveredLetterIndex > words[currentWordIndex].length) {
            reload = true;
        }
    }

    if (arduboy.justPressed(B_BUTTON)) {
        if (lastDiscoveredLetterIndex == words[currentWordIndex].length) {
            // Not working for now :/
            //reload = true;
            return;
        }

        if (screen == Screen::Letters) {
            screen = Screen::Map;
            return;
        }

        // A treasure has been found
        // We update the world map to put an opened treasure tile
        // corresponding to the letter
        if (mapGenerator.onClosedTreasure(
            dinausor.movable.x,
            dinausor.movable.y,
            dinausor.movable.size
        )) {
            screen = Screen::Letters;
            words[currentWordIndex].discoverLetter(lastDiscoveredLetterIndex);
            mapGenerator.updateTileAt(
                dinausor.movable.x,
                dinausor.movable.y,
                dinausor.movable.size,
                4,
                5
            );
            lastDiscoveredLetterIndex++;
        }
    }


    if (screen == Screen::Letters) {
        drawLetters();
    } else {
        drawMap();
    }

    // then we finaly we tell the arduboy to display what we just wrote to the display
    arduboy.display();
}

/**
 * Draws the letters
 */
void drawLetters()
{
    arduboy.setCursor(16, 30);
    words[currentWordIndex].draw(arduboy);
}

/**
 * Draws the map
 */
void drawMap()
{
    mapGenerator.draw();

    dinausor.movable.moveOnPlace = false;

    bool collision = mapGenerator.collision(
        dinausor.movable.x,
        dinausor.movable.y,
        dinausor.movable.size
    );

    if (mapGenerator.needToMoveMap(
        dinausor.movable.x,
        dinausor.movable.y,
        dinausor.movable.direction
    ) && dinausor.movable.hasSteppedPixels(1)
    && dinausor.movable.moving) {
        mapGenerator.moveMap(
            dinausor.movable.vector.x,
            dinausor.movable.vector.y,
            dinausor.movable.vx,
            dinausor.movable.vy
        );
        dinausor.movable.moveOnPlace = true;
    }

    dinausor.draw(arduboy, collision);
}

/**
 * Shuffle words
 */
void shuffleWords()
{
    for (uint8_t i; i<10; i++) {
        // Pick a random index from 0 to i
        uint8_t j = random(0, i+1);
        swapWords(&words[i], &words[j]);
    }
}

/**
 * Swap words between each others
 */
void swapWords(Word *a, Word *b) {
    Word temp = *a;
    *a = *b;
    *b = temp;
}