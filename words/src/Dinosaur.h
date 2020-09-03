#ifndef DINOSAUR_H
#define DINOSAUR_H

#include <Arduboy2.h>
#include "Movable.h"
#include "bitmaps.h"

/**
 * The dinosaur character
 */
struct Dinausor
{

    Movable movable;

    uint8_t stillBitmapIndex;
    uint8_t walkingBitmapFrame = 1;

    /**
     * Draws the dinausor, main function
     */
    void draw(Arduboy2 & arduboy, bool collision)
    {
        movable.main(arduboy, collision);
        setStillBitmapIndex();
        setWalkingBitmapFrame();

        Sprites::drawExternalMask(
            movable.x, movable.y,
            dinosaur,
            dinosaur_mask,
            stillBitmapIndex + walkingBitmapFrame * 4,
            stillBitmapIndex + walkingBitmapFrame * 4
        );
    }

    /**
     * Sets the bitmap index where the dinosaur is doing nothing,
     * according to the direction
     */
    void setStillBitmapIndex()
    {
        switch (movable.direction) {
            case Movable::Direction::Left:
                stillBitmapIndex = 0;
                break;
            case Movable::Direction::Right:
                stillBitmapIndex = 1;
                break;
            case Movable::Direction::Up:
                stillBitmapIndex = 3;
                break;
            case Movable::Direction::Down:
                stillBitmapIndex = 2;
                break;
        }
    }

    /**
     * Sets the walking bitmap frame
     */
    void setWalkingBitmapFrame()
    {
        if (!movable.moving) {
            walkingBitmapFrame = 0;
            return;
        }

        if (walkingBitmapFrame == 6) {
            walkingBitmapFrame = 1;
        }

        if (movable.hasSteppedPixels(1)) {
            walkingBitmapFrame++;
        } else {
            walkingBitmapFrame = 1;
        }
    }
};

#endif