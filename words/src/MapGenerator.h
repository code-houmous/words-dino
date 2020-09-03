#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <Arduboy2.h>

/**
 * The world map manager
 */
struct MapGenerator
{

    // Size of one tile
    #define TILE_SIZE 16

    // Types of map tiles
    #define GROUND 0
    #define WALL 1
    #define GRASS 2

    // World size
    #define WORLD_WIDTH 12
    #define WORLD_HEIGHT 6

    // The points where the character stop moving
    // on screen, and the map starts moving instead
    #define X_LIMIT_TO_MOVE_MAP 80
    #define Y_LIMIT_TO_MOVE_MAP 40

    // Number of tiles that could fit in width
    const uint8_t mapWidth = WIDTH / TILE_SIZE;

    // Number of tiles that could fit in width
    const uint8_t mapHeight = HEIGHT / TILE_SIZE;

    // Position of the map
    int16_t mapOffsetX = 0;

    // Position of the map
    int16_t mapOffsetY = 0;

    // World map
    uint8_t world[WORLD_HEIGHT][WORLD_WIDTH] = {
        {GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, WALL, GROUND, GROUND, GRASS},
        {GROUND, GROUND, GROUND, GROUND, WALL, WALL, GROUND, GROUND, GRASS, GROUND, GRASS, GROUND},
        {GROUND, GRASS, GRASS, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
        {GROUND, GRASS, GRASS, GROUND, GROUND, GROUND, GROUND, GROUND, GRASS, GRASS, GROUND, GROUND},
        {GROUND, GROUND, GROUND, GROUND, WALL, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
        {GROUND, GRASS, GRASS, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND}
    };

    // Index of tiles that represents ground
    uint8_t tilesGroundIndexes[3] = {0, 2, 4};

    // Index of tiles that represents walls
    uint8_t tilesWallIndexes[3] = {1, 3, 5};

    /**
     * Main function
     * 
     * The index of the tile is defined by the loop that takes
     * the map size as boundaries, then we add the map offset divided
     * by the tile size.
     */
    void draw()
    {
        for (uint8_t y = 0; y < mapHeight + 1; y++) {
            for (uint8_t x = 0; x < mapWidth + 1; x++) {
                drawTile(
                    x + (abs(round(mapOffsetX / TILE_SIZE))),
                    y + (abs(round(mapOffsetY / TILE_SIZE)))
                );
            }
        }
    }

    /**
     * True if the map needs to be moved on screen
     */
    bool needToMoveMap(
        const uint8_t characterPositionX,
        const uint8_t characterPositionY,
        const Movable::Direction direction
    )
    {
        // World's limit has been reached for this direction
        // so we don't move the map to avoid drawing black space
        if (worldLimitsReached(direction)) {
            return false;
        }

        if (
            direction == Movable::Direction::Right
            && characterPositionX > X_LIMIT_TO_MOVE_MAP
        ) {
            return true;
        }

        if (
            direction == Movable::Direction::Left
            && characterPositionX <= X_LIMIT_TO_MOVE_MAP + mapOffsetX
        ) {
            return true;
        }

        if (
            direction == Movable::Direction::Down
            && characterPositionY > Y_LIMIT_TO_MOVE_MAP
        ) {
            return true;
        }

        if (
            direction == Movable::Direction::Up
            && characterPositionY < Y_LIMIT_TO_MOVE_MAP + mapOffsetY
        ) {
            return true;
        }

        return false;
    }

    /**
     * Returns true when world limit has been reached
     */
    bool worldLimitsReached(Movable::Direction direction)
    {
        // World limit has been reached on right
        // if going right
        // AND the offset of the map + the left distance + the place between the char limit and the edgde screen
        // divided by tile size is greater than the world width
        if (
            direction == Movable::Direction::Right
            && (abs(mapOffsetX) + X_LIMIT_TO_MOVE_MAP + WIDTH - X_LIMIT_TO_MOVE_MAP) / TILE_SIZE >= WORLD_WIDTH
        ) {
            return true;
        }

        // World limit has been reached on bottom
        if (
            direction == Movable::Direction::Down
            && (abs(mapOffsetY) + Y_LIMIT_TO_MOVE_MAP + HEIGHT - Y_LIMIT_TO_MOVE_MAP) / TILE_SIZE >= WORLD_HEIGHT
        ) {
            return true;
        }

        // Reached on left side
        if (
            direction == Movable::Direction::Left
            && mapOffsetX >= 0
        ) {
            return true;
        }

        // Reached while going up
        if (
            direction == Movable::Direction::Up
            && mapOffsetY >= 0
        ) {
            return true;
        }

        return false;
    }

    /**
     * Sets the position of the map
     * according to the character vector movement values
     */
    void moveMap(int8_t vectorX, int8_t vectorY, double velocityX, double velocityY)
    {
        mapOffsetX = mapOffsetX - (vectorX * velocityX);
        mapOffsetY = mapOffsetY - (vectorY * velocityY);
    }

    /**
     * Draws a tile of map
     */
    void drawTile(uint8_t x, uint8_t y) {
        int8_t tileX = x * TILE_SIZE + mapOffsetX;
        int8_t tileY = y * TILE_SIZE + mapOffsetY;

        if (world[y][x] == GROUND) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                mapTile,
                tilesGroundIndexes[x % 3]
            );
        }

        if (world[y][x] == WALL) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                mapTile,
                tilesWallIndexes[x % 3]
            );
        }

        if (world[y][x] == GRASS) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                mapTile,
                6
            );
        }
    }

    bool collision(uint8_t characterX, uint8_t characterY, uint8_t size, int8_t vectorX, int8_t vectorY, Arduboy2 & arduboy)
    {
        // We calculate the 4 corners coordinates of the rectangle that represents the character
        // We also make some adjustments on its size, because our character doesn't
        // fill the whole rectangle
        uint8_t leftTile = characterX + 6;
        uint8_t rightTile = characterX + size - 6;
        uint8_t topTile = characterY + 10;
        uint8_t bottomTile = characterY + size - 2;

        for (uint8_t i = leftTile; i <= rightTile; i++) {
            for (uint8_t j = topTile; j <= bottomTile; j++) {
                if (
                    world
                        [(j + abs(mapOffsetY)) / TILE_SIZE]
                        [(i + abs(mapOffsetX)) / TILE_SIZE]
                        == WALL
                ) {
                    return true;
                }
            }
        }

        return false;
    }
};

#endif