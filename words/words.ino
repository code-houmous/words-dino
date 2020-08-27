#include <Arduboy2.h>

#include "src/Dinosaur.h"
#include "src/MapGenerator.h"

Arduboy2 arduboy;
Dinausor dinausor;
MapGenerator mapGenerator;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
    // initiate arduboy instance
    arduboy.begin();

    // here we set the framerate to 15, we do not need to run at
    // default 60 and it saves us battery life
    arduboy.setFrameRate(15);

    arduboy.initRandomSeed();
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
    // pause render until it's time for the next frame
    if (!(arduboy.nextFrame()))
        return;

    // first we clear our screen to black
    arduboy.clear();

    arduboy.pollButtons();

    mapGenerator.draw();
    dinausor.draw(arduboy);

    // then we finaly we tell the arduboy to display what we just wrote to the display
    arduboy.display();
}
