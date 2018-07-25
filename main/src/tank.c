#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

tank tank1, tank2;

void InitTankStat()
{
    tank1.x = 0;
    tank1.y = 0;
    tank1.move_dir = MOVE_STATIC;
    tank1.shoot_dir = SHOOT_DOWN;
    tank1.stat = HEALTHY;
    map[tank1.x][tank1.y] = MAP_TANK1;
    tank2.x = MAP_RANGE_X - 1;
    tank2.y = MAP_RANGE_Y - 1;
    tank2.move_dir = MOVE_STATIC;
    tank2.shoot_dir = SHOOT_UP;
    tank2.stat = HEALTHY;
    map[tank2.x][tank2.y] = MAP_TANK2;
}

void TankMove(int num)
{
    tank *tanka, *tankb;
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
    switch (tanka->move_dir)
    {
    case MOVE_UP:
        x = tanka->x;
        y = tanka->y - 1;
        break;
    case MOVE_DOWN:
        x = tanka->x;
        y = tanka->y + 1;
        break;
    case MOVE_LEFT:
        x = tanka->x - 1;
        y = tanka->y;
        break;
    case MOVE_RIGHT:
        x = tanka->x + 1;
        y = tanka->y;
        break;
    case MOVE_STATIC:
        x = tanka->x;
        y = tanka->y;
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
    case MAP_EMPTY:
        map[tanka->x][tanka->y] = MAP_EMPTY;
        tanka->x = x;
        tanka->y = y;
        if (num == 1)
            map[tanka->x][tanka->y] = MAP_TANK1;
        else
            map[tanka->x][tanka->y] = MAP_TANK2;
        break;
    case MAP_TANK1:
        if (num == 2)
        {
            tanka->stat = EXPLODE;
            tankb->stat = EXPLODE;
            map[tanka->x][tanka->y] = MAP_BOOM;
            map[x][y] = MAP_BOOM;
            break;
        }
        else
        {
            exit(-3);
        }
    case MAP_TANK2:
        if (num == 1)
        {
            tanka->stat = EXPLODE;
            tankb->stat = EXPLODE;
            map[tanka->x][tanka->y] = MAP_BOOM;
            map[x][y] = MAP_BOOM;
            break;
        }
        else
        {
            exit(-3);
        }
    case MAP_BULLET:
        tanka->stat = EXPLODE;
        map[tanka->x][tanka->y] = MAP_BOOM;
        map[x][y] = MAP_BOOM;
        break;
    case MAP_BLOCK:
        break;
    case MAP_BOOM:
        tanka->stat = EXPLODE;
        map[tanka->x][tanka->y] = MAP_EMPTY;
        tanka->x = x;
        tanka->y = y;
    default:
        exit(-3);
    }
}

void TankShoot(int num)
{
    tank *tanka, *tankb;
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
    switch (tanka->shoot_dir)
    {
    case SHOOT_UP:
        x = tanka->x;
        y = tanka->y - 1;
        break;
    case SHOOT_DOWN:
        x = tanka->x;
        y = tanka->y + 1;
        break;
    case SHOOT_LEFT:
        x = tanka->x - 1;
        y = tanka->y;
        break;
    case SHOOT_RIGHT:
        x = tanka->x + 1;
        y = tanka->y;
        break;
    default:
        fprintf(stderr, "error: -4\n");
        exit(-4);
    }
    if (x < 0 || x > MAP_RANGE_X - 1)
        return;
    if (y < 0 || y > MAP_RANGE_Y - 1)
        return;
    switch (map[x][y])
    {
    case MAP_EMPTY:
        map[x][y] = MAP_BULLET;
        switch (tanka->shoot_dir)
        {
        case SHOOT_UP:
            bullet[x][y] = BULLET_UP;
            break;
        case SHOOT_DOWN:
            bullet[x][y] = BULLET_DOWN;
            break;
        case SHOOT_LEFT:
            bullet[x][y] = BULLET_LEFT;
            break;
        case SHOOT_RIGHT:
            bullet[x][y] = BULLET_RIGHT;
            break;
        default:
            exit(-4);
        }
        break;
    case MAP_TANK1:
        map[x][y] = MAP_BOOM;
        tank1.stat = EXPLODE;
        break;
    case MAP_TANK2:
        map[x][y] = MAP_BOOM;
        tank2.stat = EXPLODE;
        break;
    case MAP_BULLET:
        map[x][y] = MAP_BOOM;
        break;
    case MAP_BLOCK:
        break;
    case MAP_BOOM:
        break;
    default:
        fprintf(stderr, "error: -4\n");
        exit(-4);
    }
}
