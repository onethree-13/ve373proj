#ifndef _GAME_H_
#define _GAME_H_
#include "bullet.h"
#include "map.h"
#include "tank.h"


#define MAP_RANGE_X 10
#define MAP_RANGE_Y 10
#define MAP_MAX ((MAP_RANGE_X)*(MAP_RANGE_Y))

extern int map[MAP_RANGE_X][MAP_RANGE_Y];
extern bullet[MAP_MAX];

enum DIRECTION
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

#endif