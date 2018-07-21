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
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void InitBulletStat()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            bullet[i][j] = BULLET_STAT::NONE;
}

void UpdateBulletStat()
{
    int i, j, x, y;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
        {
            bullet_old[i][j] = BULLET_STAT::NONE;
            if (map[i][j] == MAP_STAT::BULLET)
            {
                bullet_old[i][j] = bullet[i][j];
                map[i][j] == MAP_STAT::EMPTY;
            }
            bullet[i][j] = BULLET_STAT::NONE;
        }
    }
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
        {
            // get position of new bullet (x,y)
            if (bullet_old[i][j] == BULLET_STAT::NONE)
                continue;
            switch (bullet_old[i][j])
            {
            case BULLET_STAT::UP:
                x = i;
                y = j - 1;
                break;
            case BULLET_STAT::DOWN:
                x = i;
                y = j + 1;
                break;
            case BULLET_STAT::LEFT:
                x = i - 1;
                y = j;
                break;
            case BULLET_STAT::RIGHT:
                x = i + 1;
                y = j;
                break;
            default:
                exit(-1);
            }

            // check boundary
            if (x < 0 || x > MAP_RANGE_X - 1)
                continue;
            if (y < 0 || y > MAP_RANGE_Y - 1)
                continue;

            if (bullet_old[i][j] == BULLET_STAT::UP && bullet_old[x][y] == BULLET_STAT::DOWN)
            {
                map[i][j] = MAP_STAT::BOOM;
                map[x][y] = MAP_STAT::BOOM;
                continue;
            }
            if (bullet_old[i][j] == BULLET_STAT::DOWN && bullet_old[x][y] == BULLET_STAT::UP)
            {
                map[i][j] = MAP_STAT::BOOM;
                map[x][y] = MAP_STAT::BOOM;
                continue;
            }
            if (bullet_old[i][j] == BULLET_STAT::LEFT && bullet_old[x][y] == BULLET_STAT::RIGHT)
            {
                map[i][j] = MAP_STAT::BOOM;
                map[x][y] = MAP_STAT::BOOM;
                continue;
            }
            if (bullet_old[i][j] == BULLET_STAT::RIGHT && bullet_old[x][y] == BULLET_STAT::LEFT)
            {
                map[i][j] = MAP_STAT::BOOM;
                map[x][y] = MAP_STAT::BOOM;
                continue;
            }

            switch (map[x][y])
            {
            case MAP_STAT::EMPTY:
                if (bullet[x][y] == BULLET_STAT::NONE)
                {
                    bullet[x][y] = bullet_old[i][j];
                }
                else
                {
                    map[x][y] = MAP_STAT::BOOM;
                }
                break;
            case MAP_STAT::TANK1:
                tank1.stat = TANK_STAT::EXPLODE;
                map[x][y] = MAP_STAT::BOOM;
                break;
            case MAP_STAT::TANK2:
                tank2.stat = TANK_STAT::EXPLODE;
                map[x][y] = MAP_STAT::BOOM;
                break;
            case MAP_STAT::BULLET:
                exit(-2);
            case MAP_STAT::BLOCK:
                break;
            case MAP_STAT::BOOM:
                break;
            default:
                exit(-2);
            }
        }
    }
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            if (bullet[i][j] != BULLET_STAT::NONE)
                if (map[i][j] == MAP_STAT::BOOM)
                    bullet[i][j] = BULLET_STAT::NONE;
                else
                    map[i][j] = MAP_STAT::BULLET;
}
#endif