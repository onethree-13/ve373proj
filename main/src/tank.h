#ifndef _TANK_H_
#define _TANK_H_
#include "bullet.h"
#include "game.h"
#include "map.h"

void InitTankStat();
void CheckTankStat();
void TankMove();
void TankShoot();

struct tank
{
    int x, y;
    int stat;
};

enum TANK_STAT
{
    HEALTHY,
    EXPLODE
};

enum MOVE_DIR
{
    STATIC,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum SHOOT_DIR
{
    DEFAULT,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void InitTankStat()
{
    tank1.x = 0;
    tank1.y = 0;
    tank1.stat = TANK_STAT::HEALTHY;
    map[tank1.x][tank1.y] = MAP_STAT::TANK1;
    tank2.x = MAP_RANGE_X - 1;
    tank2.y = MAP_RANGE_Y - 1;
    tank2.move_dir = MOVE_DIR::STATIC;
    tank2.shoot_dir = SHOOT_DIR::UP;
    tank2.stat = TANK_STAT::HEALTHY;
    map[tank2.x][tank2.y] = MAP_STAT::TANK2;
}

void CheckTankStat()
{
    if (tank1.stat = TANK_STAT::EXPLODE)
    {
        if (tank2.stat = TANK_STAT::EXPLODE)
        {
            // TODO: draw;
        }
        else
        {
            // TODO: tank2 win;
        }
    }
    else
    {
        if (tank2.stat = TANK_STAT::EXPLODE)
        {
            // TODO: tank1 win;
        }
    }
}

void TankMove();
void TankShoot();

#endif