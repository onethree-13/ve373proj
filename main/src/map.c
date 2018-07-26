#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>

int map[MAP_RANGE_X][MAP_RANGE_Y];

void InitMapStat()
{
    int i, j;
    transform_counter = 0;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            map[i][j] = default_map[i][j];
}

void UpdateMapStat()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            if (map[i][j] == MAP_BOOM)
                map[i][j] = MAP_EMPTY;
}

void MapTransform()
{
    int i;
    int c = transform_counter++;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        map[i][c] = MAP_BLOCK;
        if (map[i][c] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[i][c] == MAP_TANK2)
            tank2.stat = EXPLODE;
        map[i][MAP_RANGE_Y - c - 1] = MAP_BLOCK;
        if (map[i][MAP_RANGE_Y - c - 1] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[i][MAP_RANGE_Y - c - 1] == MAP_TANK2)
            tank2.stat = EXPLODE;
    }
    for (i = 0; i < MAP_RANGE_Y; i++)
    {
        map[c][i] = MAP_BLOCK;
        if (map[c][i] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[c][i] == MAP_TANK2)
            tank2.stat = EXPLODE;
        map[MAP_RANGE_X - c - 1][i] = MAP_BLOCK;
        if (map[MAP_RANGE_X - c - 1][i] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[MAP_RANGE_X - c - 1][i] == MAP_TANK2)
            tank2.stat = EXPLODE;
    }
}