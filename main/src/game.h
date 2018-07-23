#ifndef _GAME_H_
#define _GAME_H_
#include "bullet.h"
#include "map.h"
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
int GameRound();


#endif
