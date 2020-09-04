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
    #define GRND 0
    #define WALL 1
    #define GRSS 2
    #define FLWR 3

    // World size
    #define WORLD_WIDTH 24
    #define WORLD_HEIGHT 8

    // The points where the character stop moving
    // on screen, and the map starts moving instead
    #define X_LIMIT_TO_MOVE_MAP 64
    #define Y_LIMIT_TO_MOVE_MAP 32

    // Number of tiles that could fit in width
    const uint8_t mapWidth = WIDTH / TILE_SIZE;

    // Number of tiles that could fit in width
    const uint8_t mapHeight = HEIGHT / TILE_SIZE;

    // Position of the map
    int16_t mapOffsetX = 0;

    // Position of the map
    int16_t mapOffsetY = 0;

    // first map
    uint8_t const world[WORLD_HEIGHT][WORLD_WIDTH] = {
        {GRND, GRND, GRND, GRND, GRND, GRND, WALL, GRND, WALL, WALL, WALL, WALL, GRSS, GRSS, GRSS, GRSS, GRND, GRND, GRND, GRSS, FLWR, GRSS, GRSS, FLWR},
        {GRND, GRND, WALL, WALL, WALL, GRND, GRND, GRND, WALL, WALL, GRSS, WALL, GRSS, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS},
        {GRND, GRND, WALL, FLWR, WALL, GRND, GRND, GRND, WALL, WALL, WALL, WALL, GRSS, GRND, GRSS, GRSS, GRSS, GRND, WALL, GRND, GRSS, GRND, GRND, FLWR},
        {GRND, GRND, WALL, WALL, WALL, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS, GRSS, WALL, GRND, GRND, GRND, GRND, GRND, FLWR},
        {GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS, GRND, GRSS, GRND, GRND, GRND, GRND, GRND, WALL, GRND, GRSS},
        {GRND, GRND, GRND, WALL, GRND, GRND, WALL, GRND, WALL, WALL, WALL, WALL, GRSS, GRSS, GRND, GRSS, GRND, GRND, GRND, GRSS, GRND, GRND, GRND, FLWR},
        {GRND, GRSS, GRSS, GRND, GRND, GRND, GRND, GRND, GRND, WALL, GRSS, WALL, GRSS, GRSS, GRND, WALL, WALL, WALL, GRND, GRND, GRND, GRSS, GRND, GRSS},
        {WALL, WALL, WALL, WALL, WALL, GRND, GRND, GRND, WALL, WALL, WALL, WALL, GRSS, GRSS, WALL, WALL, GRND, GRND, GRND, GRSS, FLWR, FLWR, GRSS, FLWR}
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
            && characterPositionX <= X_LIMIT_TO_MOVE_MAP
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
            && HEIGHT - characterPositionY >= Y_LIMIT_TO_MOVE_MAP
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

        if (world[y][x] == GRND) {
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

        if (world[y][x] == GRSS) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                mapTile,
                6
            );
        }

        if (world[y][x] == FLWR) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                mapTile,
                6
            );
        }
    }

    /**
     * Returns true if a body collides with a solid tile map (like a WALL)
     */
    bool collision(uint8_t bodyX, uint8_t bodyY, uint8_t bodySize, int8_t vectorX, int8_t vectorY, Arduboy2 & arduboy)
    {
        // We calculate the 4 corners coordinates of the rectangle that represents the character
        // We also make some adjustments on its size, because our character doesn't
        // fill the whole rectangle
        uint8_t leftTile = bodyX + 6;
        uint8_t rightTile = bodyX + bodySize - 6;
        uint8_t topTile = bodyY + 10;
        uint8_t bottomTile = bodyY + bodySize - 2;

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