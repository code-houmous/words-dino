#ifndef MOVABLE_H
#define MOVABLE_H

#include <Arduboy2.h>

/**
 * To make a movable item with arrows
 */
struct Movable
{

public:
    // x position
    int8_t x;

    // y position
    int8_t y;

    // speed vector
    double speed = 0.2;

    // inertia decrease
    double inertia = 0.2;

    // Is the item moving ? (true when moving and inertia)
    bool moving = false;

    // Possible directions for the movable item
    enum struct Direction {
        Left,
        Right,
        Up,
        Down
    };

    // Current direction, even when stopped
    Direction direction = Direction::Right;

private:
    // previous x position
    int8_t previousX;

    // previous y position
    int8_t previousY;

    // x velocity
    double vx = 0;

    // y velocity
    double vy = 0;

    // Max velocity
    double maxVelocity = 2;

    // true if one of the direction button is pressed
    bool action = true;

    struct Vector {
        int8_t x = 0;
        int8_t y = 0;

        void set(int8_t X, int8_t Y) {
            x = X;
            y = Y;
        };
    };

    // Vector for moving
    Vector vector;

public:
    /**
     * Main function to compute the positions
     */
    void main(Arduboy2 & arduboy) {
        changeDirection(arduboy);
        setVelocities();
        updatePosition();
    }

    /**
     * Does the moving item has run at least n pixels
     */
    bool hasSteppedPixels(uint8_t amount)
    {
        return abs(previousX - x) > amount - 1
            || abs(previousY - y) >  amount -1;
    }

private:
    /**
     * Change the item direction according to pressed
     * buttons
     */
    void changeDirection(Arduboy2 & arduboy)
    {
        // by default
        action = true;

        if (arduboy.pressed(LEFT_BUTTON)) {
            moving = true;
            vector.set(-1, 0);
            direction = Direction::Left;
            return;
        }

        if (arduboy.pressed(RIGHT_BUTTON)) {
            moving = true;
            vector.set(1, 0);
            direction = Direction::Right;
            return;
        }

        if (arduboy.pressed(UP_BUTTON)) {
            moving = true;
            vector.set(0, -1);
            direction = Direction::Up;
            return;
        }

        if (arduboy.pressed(DOWN_BUTTON)) {
            moving = true;
            vector.set(0, 1);
            direction = Direction::Down;
            return;
        }

        // None of the direction button is pressed
        action = false;
    }

    /**
     * Sets the velocities according to direction
     */
    void setVelocities()
    {
        if (!moving) {
            // stopped
            vx = 0;
            vy = 0;

            return;
        }

        if (!action) {
            // intertia
            vx = vx - speed;
            vy = vy - speed;

            if (vx < 0) {
                vx = 0;
            }

            if (vy < 0) {
                vy = 0;
            }

            if (vx == 0 && vy == 0) {
                moving = false;
            }

            return;
        }

        // moving
        vx = vx + speed;
        vy = vy + speed;

        if (vx > maxVelocity) {
            vx = maxVelocity;
        }

        if (vy > maxVelocity) {
            vy = maxVelocity;
        }
    }

    /**
     * Sets the position of the movable item
     * taking in account the velocity and the movement
     */
    void updatePosition()
    {
        previousX = x;
        previousY = y;

        x += vx * vector.x;
        y += vy * vector.y;
    }
};

#endif MOVABLE_H