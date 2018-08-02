#ifndef _MAP_H_
#define _MAP_H_
#include "bullet.h"
#include "tank.h"
#include "game.h"
#include "uart.h"

void InitMapStat();
void UpdateMapStat();
void MapTransform();
void SendMap();

#define MAP_RANGE_X 10
#define MAP_RANGE_Y 10
#define MAP_MAX 100

extern int map[MAP_RANGE_X][MAP_RANGE_Y];
static int transform_counter;

enum MAP_STAT
{
    MAP_EMPTY,
    MAP_TANK1,
    MAP_TANK2,
    MAP_BULLET,
    MAP_BLOCK,
    MAP_BOOM
};

static int default_map[MAP_RANGE_X][MAP_RANGE_Y] = {
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
    MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, MAP_EMPTY, //
};


#endif
