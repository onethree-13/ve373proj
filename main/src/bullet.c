#include "map.h"
#include "bullet.h"
#include "tank.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

// #define DEBUG_BULLET

int bullet[MAP_RANGE_X][MAP_RANGE_Y];

void InitBulletStat()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            bullet[i][j] = BULLET_NONE;
}

#ifdef DEBUG_BULLET

const char *GetDirName(enum BULLET_STAT stat)
{
    switch (stat)
    {
    case BULLET_NONE:
        return "0";
    case BULLET_UP:
        return "UP";
    case BULLET_DOWN:
        return "DOWN";
    case BULLET_LEFT:
        return "LEFT";
    case BULLET_RIGHT:
        return "RIGHT";
    }
}

void DisplayBullet()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
            printf("%s\t", GetDirName(bullet[j][i]));
        printf("\n");
    }
}

#endif

void UpdateBulletStat()
{
#ifdef DEBUG_BULLET
    printf("Before Update\n");
    DisplayBullet();
    getchar();
#endif
    int i, j, x, y;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
        {
            bullet_old[i][j] = BULLET_NONE;
            if (map[i][j] == MAP_BULLET)
            {
                if (bullet[i][j] == BULLET_NONE)
                {
                    fprintf(stderr, "error: -5\n");
                    exit(-5);
                }
                bullet_old[i][j] = bullet[i][j];
                map[i][j] = MAP_EMPTY;
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
                    map[x][y] = MAP_BULLET;
                }
                break;
            case MAP_TANK1:
                TakeDamage(&tank1, BULLET_DMG);
                break;
            case MAP_TANK2:
                TakeDamage(&tank2, BULLET_DMG);
                break;
            case MAP_BULLET:
                map[x][y] = MAP_BOOM;
                break;
            case MAP_BLOCK:
                break;
            case MAP_BOOM:
                break;
            default:
                fprintf(stderr, "error: -2\n");
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
#ifdef DEBUG_BULLET
    printf("update bullet\n");
    DisplayBullet();
    getchar();
#endif
}
