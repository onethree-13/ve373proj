#ifndef _TANK_H_
#define _TANK_H_
#include "bullet.h"
#include "game.h"
#include "map.h"

enum TANK_STAT
{
    HEALTHY = 0,
    TOXIC = 1,
    WIN = 2,
    LOSE = 3
};

struct tank
{
    int x, y;
    int move_dir;
    int turret_dir;
    int HP;
    int stat;
};

#endif