#ifndef _GAME_H_
#define _GAME_H_
#include "bullet.h"
#include "map.h"
#include "tank.h"

#define MAP_RANGE_X 10
#define MAP_RANGE_Y 10
#define MAP_MAX 100

extern int map[MAP_RANGE_X][MAP_RANGE_Y];
extern tank tank1, tank2;

#endif