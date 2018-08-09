#include "map.h"
#include "game.h"
#include "bullet.h"
#include "tank.h"

#include <stdlib.h>

void GameStart()
{
    InitMapStat();
    asm("NOP");
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

void GameRound()
{
#ifdef _UART_H_
    UpdateTankDir();
#endif
    TankMove(1);
    TankMove(2);
    TankShoot(1);
    TankShoot(2);
    UpdateBulletStat();
    UpdateMapStat();
    UpdateBulletStat();
    UpdateMapStat();
}

#ifdef _UART_H_

void SendGameStat(int stat)
{
    U1_TX(0x37);
    switch (stat)
    {
    case TANK1_WIN:
        U1_TX(0x3A);
        break;
    case TANK2_WIN:
        U1_TX(0x3B);
        break;
    case DRAW:
        U1_TX(0x3C);
        break;
    }
}

#endif