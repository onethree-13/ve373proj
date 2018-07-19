#ifndef _MAP_H_
#define _MAP_H_
#include "bullet.h"
#include "tank.h"
#define MAP_RANGE_X 10
#define MAP_RANGE_Y 10

extern int map[MAP_RANGE_X][MAP_RANGE_Y];

enum MAP_STAT
{
    EMPTY = 0,
    TANK1_OCCUPY = 1,
    TANK2_OCCUPY = 2,
    BULLET1 = 3,
    BULLET2 = 4,
    OBSTACLE = 5,
    POISON = 6
};

#endif