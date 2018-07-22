#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>

void InitBulletStat()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            bullet[i][j] = BULLET_NONE;
}

void UpdateBulletStat()
{
    int i, j, x, y;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
        {
            bullet_old[i][j] = BULLET_NONE;
            if (map[i][j] == MAP_BULLET)
            {
                bullet_old[i][j] = bullet[i][j];
                map[i][j] == MAP_EMPTY;
            }
            bullet[i][j] = BULLET_NONE;
        }
    }
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
        {
            // get position of new bullet (x,y)
            if (bullet_old[i][j] == BULLET_NONE)
                continue;
            switch (bullet_old[i][j])
            {
            case BULLET_UP:
                x = i;
                y = j - 1;
                break;
            case BULLET_DOWN:
                x = i;
                y = j + 1;
                break;
            case BULLET_LEFT:
                x = i - 1;
                y = j;
                break;
            case BULLET_RIGHT:
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

            if (bullet_old[i][j] == BULLET_UP && bullet_old[x][y] == BULLET_DOWN)
            {
                map[i][j] = MAP_BOOM;
                map[x][y] = MAP_BOOM;
                continue;
            }
            if (bullet_old[i][j] == BULLET_DOWN && bullet_old[x][y] == BULLET_UP)
            {
                map[i][j] = MAP_BOOM;
                map[x][y] = MAP_BOOM;
                continue;
            }
            if (bullet_old[i][j] == BULLET_LEFT && bullet_old[x][y] == BULLET_RIGHT)
            {
                map[i][j] = MAP_BOOM;
                map[x][y] = MAP_BOOM;
                continue;
            }
            if (bullet_old[i][j] == BULLET_RIGHT && bullet_old[x][y] == BULLET_LEFT)
            {
                map[i][j] = MAP_BOOM;
                map[x][y] = MAP_BOOM;
                continue;
            }

            switch (map[x][y])
            {
            case MAP_EMPTY:
                if (bullet[x][y] == BULLET_NONE)
                {
                    bullet[x][y] = bullet_old[i][j];
                }
                else
                {
                    map[x][y] = MAP_BOOM;
                }
                break;
            case MAP_TANK1:
                tank1.stat = EXPLODE;
                map[x][y] = MAP_BOOM;
                break;
            case MAP_TANK2:
                tank2.stat = EXPLODE;
                map[x][y] = MAP_BOOM;
                break;
            case MAP_BULLET:
                exit(-2);
            case MAP_BLOCK:
                break;
            case MAP_BOOM:
                break;
            default:
                exit(-2);
            }
        }
    }
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            if (bullet[i][j] != BULLET_NONE)
                if (map[i][j] == MAP_BOOM)
                    bullet[i][j] = BULLET_NONE;
                else
                    map[i][j] = MAP_BULLET;
}