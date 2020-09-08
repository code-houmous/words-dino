#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <Arduboy2.h>
#include "Word.h"

/**
 * The world map manager
 */
struct MapGenerator
{

    // Size of one tile
    #define TILE_SIZE 16

    // Types of map tiles
    const uint8_t PROGMEM GRND = 0;
    const uint8_t PROGMEM WALL = 1;
    const uint8_t PROGMEM GRSS = 2;
    const uint8_t PROGMEM FLWR = 3;
    const uint8_t PROGMEM TRSRCLOSED = 4;
    const uint8_t PROGMEM TRSROPENED = 5;

    // World size
    #define WORLD_WIDTH 23
    #define WORLD_HEIGHT 8

    // The points where the character stop moving
    // on screen, and the map starts moving instead
    const uint8_t PROGMEM X_LIMIT_TO_MOVE_MAP = 64;
    const uint8_t PROGMEM Y_LIMIT_TO_MOVE_MAP = 32;

    // Number of tiles that could fit in width
    const uint8_t PROGMEM mapWidth = WIDTH / TILE_SIZE;

    // Number of tiles that could fit in width
    const uint8_t PROGMEM mapHeight = HEIGHT / TILE_SIZE;

    // Position of the map
    int16_t mapOffsetX = 0;

    // Position of the map
    int16_t mapOffsetY = 0;

    // A struct to help us to store coordinates of some tiles
    struct Coordinates {
        uint8_t x;
        uint8_t y;
    };

    // Coordinates where we can put a treasure
    // Size is defined by the world size divided by 2
    // because let's say 50% of the world is walkable
    // We are going to fill this array by going through
    // the world starting by the end, so the treasures have more chance
    // to be far from the player
    Coordinates walkableTiles[WORLD_HEIGHT * WORLD_WIDTH / 2];

    // Amount of walkable tiles
    uint8_t numberOfWalkableTiles = 0;

    // first map
    uint8_t PROGMEM maps[2][WORLD_HEIGHT][WORLD_WIDTH] = {
        {
        {GRND, GRND, GRND, GRND, GRND, GRND, WALL, GRND, WALL, WALL, WALL, GRSS, GRSS, GRSS, GRSS, GRND, GRND, GRND, GRSS, FLWR, GRSS, GRSS, FLWR},
        {GRND, GRND, WALL, WALL, WALL, GRND, GRND, GRND, WALL, WALL, FLWR, GRSS, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS},
        {GRND, GRND, WALL, FLWR, WALL, GRND, GRND, GRND, WALL, WALL, WALL, GRSS, GRND, GRSS, GRSS, GRSS, GRND, WALL, GRND, GRSS, GRND, GRND, FLWR},
        {GRND, GRND, WALL, WALL, WALL, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS, GRSS, WALL, GRND, GRND, GRND, GRND, GRND, FLWR},
        {GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS, GRND, GRSS, GRND, GRND, GRND, GRND, GRND, WALL, GRND, GRSS},
        {GRND, GRND, GRND, WALL, GRND, GRND, WALL, GRND, WALL, WALL, WALL, GRSS, GRSS, GRND, GRSS, GRND, GRND, GRND, GRSS, GRND, GRND, GRND, FLWR},
        {GRND, GRSS, GRSS, GRND, GRND, GRND, GRND, GRND, GRND, WALL, FLWR, GRSS, GRSS, GRND, WALL, WALL, WALL, GRND, GRND, GRND, GRSS, GRND, GRSS},
        {WALL, WALL, WALL, WALL, WALL, GRND, GRND, GRND, WALL, WALL, WALL, GRSS, GRSS, WALL, WALL, GRND, GRND, GRND, GRSS, FLWR, FLWR, GRSS, FLWR}
        },
        {
        {GRND, GRND, GRND, GRND, GRND, GRND, WALL, GRND, WALL, WALL, WALL, GRSS, GRSS, GRSS, GRSS, GRND, GRND, GRND, GRSS, FLWR, GRSS, GRSS, FLWR},
        {GRND, GRND, WALL, WALL, WALL, GRND, GRND, GRND, WALL, WALL, FLWR, GRSS, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS},
        {GRND, GRND, WALL, FLWR, WALL, GRND, GRND, GRND, WALL, WALL, WALL, GRSS, GRND, GRSS, GRSS, GRSS, GRND, WALL, GRND, GRSS, GRND, GRND, FLWR},
        {GRND, GRND, WALL, WALL, WALL, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS, GRSS, WALL, GRND, GRND, GRND, GRND, GRND, FLWR},
        {GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRND, GRSS, GRND, GRSS, GRND, GRND, GRND, GRND, GRND, WALL, GRND, GRSS},
        {GRND, GRND, GRND, WALL, GRND, GRND, WALL, GRND, WALL, WALL, WALL, GRSS, GRSS, GRND, GRSS, GRND, GRND, GRND, GRSS, GRND, GRND, GRND, FLWR},
        {GRND, GRSS, GRSS, GRND, GRND, GRND, GRND, GRND, GRND, WALL, FLWR, GRSS, GRSS, GRND, WALL, WALL, WALL, GRND, GRND, GRND, GRSS, GRND, GRSS},
        {WALL, WALL, WALL, WALL, WALL, GRND, GRND, GRND, WALL, WALL, WALL, GRSS, GRSS, WALL, WALL, GRND, GRND, GRND, GRSS, FLWR, FLWR, GRSS, FLWR}
        }
    };

    // first map
    uint8_t world[WORLD_HEIGHT][WORLD_WIDTH];

    // Index of tiles that represents ground
    uint8_t tilesGroundIndexes[3] = {0, 2, 4};

    // Index of tiles that represents walls
    uint8_t tilesWallIndexes[3] = {1, 3, 5};

    void newMap()
    {
        // Chosing randomly the map
        uint8_t map = random(0, 1);

        // Getting the world
        for (uint8_t y = 0; y < WORLD_HEIGHT; y++) {
            for (uint8_t x = 0; x < WORLD_WIDTH; x++) {
                world[y][x] = maps[map][y][x];
            }
        }

        // Erasing the walkable tiles
        uint8_t index = 0;
        for (uint8_t i=0; i<WORLD_HEIGHT*WORLD_WIDTH; i++) {
            walkableTiles[i] = Coordinates();
        }

        // We reference all walkable tiles
        for (int8_t y = WORLD_HEIGHT; y >= 0; y=y-2) {
            for (int8_t x = WORLD_WIDTH; x >= 0; x=x-2) {
                if (world[y][x] == GRND) {
                    Coordinates c;
                    c.x = x;
                    c.y = y;
                    walkableTiles[index] = c;

                    index++;
                }
            }
        }

        numberOfWalkableTiles = index - 1;
    }

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
                7
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

        if (world[y][x] == TRSRCLOSED) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                treasureTile,
                0
            );
        }

        if (world[y][x] == TRSROPENED) {
            Sprites::drawOverwrite(
                tileX,
                tileY,
                treasureTile,
                2
            );
        }
    }

    /**
     * Returns true if a body collides with a solid tile map (like a WALL)
     */
    bool collision(uint8_t bodyX, uint8_t bodyY, uint8_t bodySize)
    {
        return tileAt(bodyX, bodyY, bodySize, WALL);
    }

    /**
     * Returns true if a body collides with a solid tile map (like a WALL)
     */
    bool onClosedTreasure(uint8_t bodyX, uint8_t bodyY, uint8_t bodySize)
    {
        return tileAt(bodyX, bodyY, bodySize, TRSRCLOSED);
    }

    /**
     * Returns true if the body collides with a given tile type
     */
    bool tileAt(uint8_t bodyX, uint8_t bodyY, uint8_t bodySize, uint8_t tileType) {
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
                        == tileType
                ) {
                    return true;
                }
            }
        }

        return false;
    }

    /**
     * Update a tile type
     */
    void updateTileAt(uint8_t bodyX, uint8_t bodyY, uint8_t bodySize, uint8_t tileType, uint8_t toType) {
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
                        == tileType
                ) {
                    world
                        [(j + abs(mapOffsetY)) / TILE_SIZE]
                        [(i + abs(mapOffsetX)) / TILE_SIZE]
                        = toType;
                }
            }
        }
    }


    /**
     * Dispose treasures randomly across the map
     */
    void putTreasuresRandomly(Word word) {
        // Shuffle the walkable tiles table
        for (uint8_t i; i<numberOfWalkableTiles; i++) {
            // Pick a random index from 0 to i
            uint8_t j = random(0, i+1);
            swapCoordinates(&walkableTiles[i], &walkableTiles[j]);
        }

        for (uint8_t i=0; i<word.length; i++) {
            world[walkableTiles[i].y][walkableTiles[i].x] = TRSRCLOSED;
        }
    }

    /**
     * Swap coordinates of walkable tiles between each others
     */
    void swapCoordinates(Coordinates *a, Coordinates *b) {
        Coordinates temp = *a;
        *a = *b;
        *b = temp;
    }
};

#endif