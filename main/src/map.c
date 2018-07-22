#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>

int map[MAP_RANGE_X][MAP_RANGE_Y];

void InitMapStat()
{
    int i, j;
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
