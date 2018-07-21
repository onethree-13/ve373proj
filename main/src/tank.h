#ifndef _TANK_H_
#define _TANK_H_
#include "bullet.h"
#include "game.h"
#include "map.h"

void InitTankStat();
void UpdateTankDir();
/* TODO: Qianyong Tang
/* Update tank1.move_dir
/* Update tank2.move_dir
/* Update tank1.shoot_dir
/* Update tank2.shoot_dir
*/
void TankMove(int num);
void TankShoot(int num);

struct tank
{
    int x, y;
    int stat;
    int move_dir;
    int shoot_dir;
};

enum TANK_STAT
{
    HEALTHY,
    EXPLODE
};

enum MOVE_DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STATIC,
};

enum SHOOT_DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void InitTankStat()
{
    tank1.x = 0;
    tank1.y = 0;
    tank1.move_dir = MOVE_DIR::STATIC;
    tank1.shoot_dir = SHOOT_DIR::DOWN;
    tank1.stat = TANK_STAT::HEALTHY;
    map[tank1.x][tank1.y] = MAP_STAT::TANK1;
    tank2.x = MAP_RANGE_X - 1;
    tank2.y = MAP_RANGE_Y - 1;
    tank2.move_dir = MOVE_DIR::STATIC;
    tank2.shoot_dir = SHOOT_DIR::UP;
    tank2.stat = TANK_STAT::HEALTHY;
    map[tank2.x][tank2.y] = MAP_STAT::TANK2;
}

void TankMove(int num)
{
    tank tanka, tankb;
    if (num == 1)
    {
        tanka = &tank1;
        tankb = &tank2;
    }
    else if (num == 2)
    {
        tanka = &tank2;
        tankb = &tank1;
    }
    else
    {
        exit(-4);
    }
    int x, y;
    switch (tanka.move_dir)
    {
    case MOVE_DIR::UP:
        x = tanka.x;
        y = tanka.y - 1;
        break;
    case MOVE_DIR::DOWN:
        x = tanka.x;
        y = tanka.y + 1;
        break;
    case MOVE_DIR::LEFT:
        x = tanka.x - 1;
        y = tanka.y;
        break;
    case MOVE_DIR::RIGHT:
        x = tanka.x + 1;
        y = tanka.y;
        break;
    case MOVE_DIR::STATIC:
        x = tanka.x;
        y = tanka.y;
        return;
    default:
        exit(-3);
    }
    if (x < 0 || x > MAP_RANGE_X - 1)
        return;
    if (y < 0 || y > MAP_RANGE_Y - 1)
        return;
    switch (map[x][y])
    {
    case MAP_STAT::EMPTY:
        map[tanka.x][tanka.y] = MAP_STAT::EMPTY;
        tanka.x = x;
        tanka.y = y;
        if (num == 1)
            map[tanka.x][tanka.y] = MAP_STAT::TANK1;
        else
            map[tanka.x][tanka.y] = MAP_STAT::TANK2;
        break;
    case MAP_STAT::TANK1:
        if (num == 2)
        {
            tanka.stat = TANK_STAT::EXPLODE;
            tankb.stat = TANK_STAT::EXPLODE;
            map[tanka.x][tanka.y] = MAP_STAT::BOOM;
            map[x][y] = MAP_STAT::BOOM;
            break;
        }
        else
        {
            exit(-3);
        }
    case MAP_STAT::TANK2:
        if (num == 1)
        {
            tanka.stat = TANK_STAT::EXPLODE;
            tankb.stat = TANK_STAT::EXPLODE;
            map[tanka.x][tanka.y] = MAP_STAT::BOOM;
            map[x][y] = MAP_STAT::BOOM;
            break;
        }
        else
        {
            exit(-3);
        }
    case MAP_STAT::BULLET:
        tanka.stat = TANK_STAT::EXPLODE;
        map[tanka.x][tanka.y] = MAP_STAT::BOOM;
        map[x][y] = MAP_STAT::BOOM;
        break;
    case MAP_STAT::BLOCK:
        break;
    case MAP_STAT::BOOM:
        tanka.stat = TANK_STAT::EXPLODE;
        map[tanka.x][tanka.y] = MAP_STAT::EMPTY;
        tanka.x = x;
        tanka.y = y;
    default:
        exit(-3);
    }
}

void TankShoot(int num)
{
    tank tanka, tankb;
    if (num == 1)
    {
        tanka = &tank1;
        tankb = &tank2;
    }
    else if (num == 2)
    {
        tanka = &tank2;
        tankb = &tank1;
    }
    else
    {
        exit(-4);
    }
    int x, y;
    switch (tanka.shoot_dir)
    {
    case SHOOT_DIR::UP:
        x = tanka.x;
        y = tanka.y - 1;
        break;
    case SHOOT_DIR::DOWN:
        x = tanka.x;
        y = tanka.y + 1;
        break;
    case SHOOT_DIR::LEFT:
        x = tanka.x - 1;
        y = tanka.y;
        break;
    case SHOOT_DIR::RIGHT:
        x = tanka.x + 1;
        y = tanka.y;
        break;
    default:
        exit(-4);
    }
    if (x < 0 || x > MAP_RANGE_X - 1)
        return;
    if (y < 0 || y > MAP_RANGE_Y - 1)
        return;
    switch (map[x][y])
    {
    case MAP_STAT::EMPTY:
        map[x][y] = MAP_STAT::BULLET;
        switch (tanka.shoot_dir)
        {
        case SHOOT_DIR::UP:
            bullet[x][y] = BULLET_STAT::UP;
            break;
        case SHOOT_DIR::DOWN:
            bullet[x][y] = BULLET_STAT::DOWN;
            break;
        case SHOOT_DIR::LEFT:
            bullet[x][y] = BULLET_STAT::LEFT;
            break;
        case SHOOT_DIR::RIGHT:
            bullet[x][y] = BULLET_STAT::RIGHT;
            break;
        default:
            exit(-4);
        }
        break;
    case MAP_STAT::TANK1:
        map[x][y] = MAP_STAT::BOOM;
        tank1.stat = TANK_STAT::EXPLODE;
        break;
    case MAP_STAT::TANK2:
        map[x][y] = MAP_STAT::BOOM;
        tank2.stat = TANK_STAT::EXPLODE;
        break;
    case MAP_STAT::BULLET:
        map[x][y] = MAP_STAT::BOOM;
        break;
    case MAP_STAT::BLOCK:
        break;
    case MAP_STAT::BOOM:
        break;
    default:
        exit(-4);
    }
}

#endif