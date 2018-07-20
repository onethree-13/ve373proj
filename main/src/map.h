#ifndef _MAP_H_
#define _MAP_H_
#include "bullet.h"
#include "tank.h"
#include "game.h"

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