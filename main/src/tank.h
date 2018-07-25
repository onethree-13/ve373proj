#ifndef _TANK_H_
#define _TANK_H_
#include "bullet.h"
#include "game.h"
#include "map.h"
#define INITIAL_HP 3
#define BULLET_DMG 1
#define CRUSHING_DMG 1
#define CRUSHED_DMG 3
#define WALL_DMG 3

typedef struct
{
    int x;
    int y;
    int stat;
    int move_dir;
    int shoot_dir;
    int HP;
} tank;

extern tank tank1, tank2;

enum TANK_STAT
{
    HEALTHY,
    EXPLODE
};

enum MOVE_DIR
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_STATIC,
};

enum SHOOT_DIR
{
    SHOOT_UP,
    SHOOT_DOWN,
    SHOOT_LEFT,
    SHOOT_RIGHT
};

void InitTankStat();
void TankMove(int num);
void TankShoot(int num);
void TakeDamage(tank* tanka, int damage);

#endif
