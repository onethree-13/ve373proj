#ifndef _MAP_H_
#define _MAP_H_
#include "bullet.h"
#include "tank.h"
#include "game.h"

void InitMapStat();

void CheckTankStat();
void UpdateMapStat();

enum MAP_STAT
{
    EMPTY,
    TANK1,
    TANK2,
    BULLET,
    BLOCK,
    BOOM
};

static default_map[MAP_RANGE_X][MAP_RANGE_Y] = {
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, //
};

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
            if (map[i][j] == MAP_STAT::BOOM)
                map[i][j] = MAP_STAT::EMPTY;
}

#endif