#include "map.h"
#include "bullet.h"
#include "tank.h"
#include "game.h"

#include <stdlib.h>

int map[MAP_RANGE_X][MAP_RANGE_Y];

void InitMapStat()
{
    int i, j;
    transform_counter = 0;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            map[i][j] = default_map[i][j];
}

void UpdateMapStat()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
        for (j = 0; j < MAP_RANGE_Y; j++)
            if (map[i][j] == MAP_BOOM)
                map[i][j] = MAP_EMPTY;
}

void MapTransform()
{
    int i;
    int c = transform_counter++;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        map[i][c] = MAP_BLOCK;
        if (map[i][c] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[i][c] == MAP_TANK2)
            tank2.stat = EXPLODE;
        map[i][MAP_RANGE_Y - c - 1] = MAP_BLOCK;
        if (map[i][MAP_RANGE_Y - c - 1] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[i][MAP_RANGE_Y - c - 1] == MAP_TANK2)
            tank2.stat = EXPLODE;
    }
    for (i = 0; i < MAP_RANGE_Y; i++)
    {
        map[c][i] = MAP_BLOCK;
        if (map[c][i] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[c][i] == MAP_TANK2)
            tank2.stat = EXPLODE;
        map[MAP_RANGE_X - c - 1][i] = MAP_BLOCK;
        if (map[MAP_RANGE_X - c - 1][i] == MAP_TANK1)
            tank1.stat = EXPLODE;
        if (map[MAP_RANGE_X - c - 1][i] == MAP_TANK2)
            tank2.stat = EXPLODE;
    }
}

void SendMap()
{
    int i, j;
    char data;
    U1_TX(0x38);
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
        {
            switch (map[i][j])
            {
            case MAP_EMPTY:
            case MAP_BOOM:
                data = 0x30;
                break;
            case MAP_BULLET:
                data = 0x31;
                break;
            case MAP_BLOCK:
                data = 0x32;
                break;
            case MAP_TANK1:
                switch (tank1.move_dir)
                {
                case MOVE_UP:
                    data = 0x33;
                    break;
                case MOVE_DOWN:
                    data = 0x34;
                    break;
                case MOVE_LEFT:
                    data = 0x35;
                    break;
                case MOVE_RIGHT:
                    data = 0x36;
                    break;
                case MOVE_STATIC:
                    data = 0x33;
                    break;
                }
                break;
            case MAP_TANK2:
                switch (tank2.move_dir)
                {
                case MOVE_UP:
                    data = 0x41;
                    break;
                case MOVE_DOWN:
                    data = 0x42;
                    break;
                case MOVE_LEFT:
                    data = 0x43;
                    break;
                case MOVE_RIGHT:
                    data = 0x44;
                    break;
                case MOVE_STATIC:
                    data = 0x41;
                    break;
                }
                break;
            }
            U1_TX(data);
        }
    }
    U1_TX(0x39);
}
