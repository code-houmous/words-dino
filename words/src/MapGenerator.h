#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <Arduboy2.h>

/**
 * The world map manager
 */
struct MapGenerator
{

    #define TILE_SIZE 16
    #define GROUND 0
    #define WALL 1

    uint8_t world[4][8] = {
        {GROUND, GROUND, GROUND, GROUND, WALL, WALL, WALL, WALL},
        {GROUND, GROUND, GROUND, GROUND, WALL, WALL, WALL, WALL},
        {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
        {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND}
    };

    uint8_t tilesGroundIndexes[3] = {0, 2, 4};
    uint8_t tilesWallIndexes[3] = {1, 3, 5};

    void draw()
    {
        for (uint8_t y = 0; y < 4; y++) {
            for (uint8_t x = 0; x < 20; x++) {
                drawTile(x, y);
            }
        }
    }

    void drawTile(uint8_t x, uint8_t y) {
        if (world[y][x] == GROUND) {
            Sprites::drawOverwrite(x * TILE_SIZE, y * TILE_SIZE, mapTile, 0);
        }

        if (world[y][x] == WALL) {
            Sprites::drawOverwrite(x * TILE_SIZE, y * TILE_SIZE, mapTile, 1);
        }
    }
};

#endif