#ifndef _GAME_H_
#define _GAME_H_
#include "map.h"
#include "bullet.h"
#include "tank.h"

enum GAME_STAT
{
    RUNNING,
    TANK1_WIN,
    TANK2_WIN,
    DRAW
};
void GameStart();
int CheckGameStat();
void GameRound();
void SendGameStat(int stat);

#endif
