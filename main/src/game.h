#ifndef _GAME_H_
#define _GAME_H_
#include "bullet.h"
#include "map.h"
#include "tank.h"

#define MAP_RANGE_X 10
#define MAP_RANGE_Y 10
#define MAP_MAX 100

extern int map[MAP_RANGE_X][MAP_RANGE_Y];
extern tank tank1, tank2;

enum GAME_STAT
{
    RUNNING,
    TANK1_WIN,
    TANK2_WIN,
    DRAW
};
void GameStart();
int CheckGameStat();
int GameRound();

void GameStart()
{
    InitMapStat();
    InitTankStat();
}

int CheckGameStat()
{
    if (tank1.stat = TANK_STAT::EXPLODE)
        if (tank2.stat = TANK_STAT::EXPLODE)
            return GAME_STAT::DRAW;
        else
            return GAME_STAT::TANK2_WIN;
    else if (tank2.stat = TANK_STAT::EXPLODE)
        return GAME_STAT::TANK1_WIN;
    return RUNNING;
}

#ifndef DEBUG_WYM
int GameRound()
{
    UpdateMapStat();
    UpdateTankDir();
    TankMove(1);
    TankMove(2);
    TankShoot(1);
    TankShoot(2);
    UpdateBulletStat();
    UpdateMapStat();
    UpdateBulletStat();
    return CheckGameStat();
}
#endif

#endif