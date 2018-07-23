#ifndef _BULLET_H_
#define _BULLET_H_

#include "map.h"
#include "tank.h"
#include "game.h"

static int bullet[MAP_RANGE_X][MAP_RANGE_Y];
static int bullet_old[MAP_RANGE_X][MAP_RANGE_Y];

void InitBulletStat();
void UpdateBulletStat();

enum BULLET_STAT
{
    BULLET_NONE,
    BULLET_UP,
    BULLET_DOWN,
    BULLET_LEFT,
    BULLET_RIGHT
};

#endif
