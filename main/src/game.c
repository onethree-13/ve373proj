#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>

void GameStart()
{
    InitMapStat();
    InitTankStat();
    InitBulletStat();
}

int CheckGameStat()
{
    if (tank1.stat == EXPLODE)
        if (tank2.stat == EXPLODE)
            return DRAW;
        else
            return TANK2_WIN;
    else if (tank2.stat == EXPLODE)
        return TANK1_WIN;
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