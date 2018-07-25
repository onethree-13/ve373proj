#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

tank tank1, tank2;

void InitTankStat()
{
    tank1.x = 0;
    tank1.y = 0;
    tank1.move_dir = MOVE_STATIC;
    tank1.shoot_dir = SHOOT_DOWN;
    tank1.stat = HEALTHY;
    tank1.HP = INITIAL_HP;
    map[tank1.x][tank1.y] = MAP_TANK1;
    tank2.x = MAP_RANGE_X - 1;
    tank2.y = MAP_RANGE_Y - 1;
    tank2.move_dir = MOVE_STATIC;
    tank2.shoot_dir = SHOOT_UP;
    tank2.stat = HEALTHY;
    map[tank2.x][tank2.y] = MAP_TANK2;
<<<<<<< HEAD
    tank2.HP = INITIAL_HP;
=======
//<<<<<<< HEAD
//=======
    tank2.HP = INITIAL_HP;    
//>>>>>>> 97bf9e950044f9296b94aa47243163fd775d5174
>>>>>>> 3f7b970e7bb1819661119b11aaee55bb2ce2aa17
}

void TankMove(int num)
{
    tank *tanka, *tankb;
    if (num == 1)
    {
        tanka = &tank1;
        tankb = &tank2;
    }
    else if (num == 2)
    {
        tanka = &tank2;
        tankb = &tank1;
    }
    else
    {
        exit(-4);
    }
    int x, y;
    switch (tanka->move_dir)
    {
    case MOVE_UP:
        x = tanka->x;
        y = tanka->y - 1;
        break;
    case MOVE_DOWN:
        x = tanka->x;
        y = tanka->y + 1;
        break;
    case MOVE_LEFT:
        x = tanka->x - 1;
        y = tanka->y;
        break;
    case MOVE_RIGHT:
        x = tanka->x + 1;
        y = tanka->y;
        break;
    case MOVE_STATIC:
        x = tanka->x;
        y = tanka->y;
        return;
    default:
        exit(-3);
    }
    if (x < 0 || x > MAP_RANGE_X - 1)
        return;
    if (y < 0 || y > MAP_RANGE_Y - 1)
        return;
    switch (map[x][y])
    {
    case MAP_EMPTY:
        map[tanka->x][tanka->y] = MAP_EMPTY;
        tanka->x = x;
        tanka->y = y;
        map[tanka->x][tanka->y] = (num == 1) ? MAP_TANK1 : MAP_TANK2;
        break;
    case MAP_TANK1:
        if (num == 2)
        {
            TakeDamage(tanka, CRUSHING_DMG);
            TakeDamage(tankb, CRUSHED_DMG);
            break;
        }
        else
        {
            fprintf(stderr, "error: -3\n");
            exit(-3);
        }
    case MAP_TANK2:
        if (num == 1)
        {
            TakeDamage(tanka, CRUSHING_DMG);
            TakeDamage(tankb, CRUSHED_DMG);
            break;
        }
        else
        {
            fprintf(stderr, "error: -3\n");
            exit(-3);
        }
    case MAP_BULLET:
        map[tanka->x][tanka->y] = MAP_EMPTY;
        tanka->x = x;
        tanka->y = y;
        map[tanka->x][tanka->y] = (num == 1) ? MAP_TANK1 : MAP_TANK2;
        TakeDamage(tankb, BULLET_DMG);
        break;
    case MAP_BLOCK:
        break;
    case MAP_BOOM:
        fprintf(stderr, "error: -3\n");
        exit(-3);
    default:
        fprintf(stderr, "error: -3\n");
        exit(-3);
    }
}

void TankShoot(int num)
{
    tank *tanka, *tankb;
    if (num == 1)
    {
        tanka = &tank1;
        tankb = &tank2;
    }
    else if (num == 2)
    {
        tanka = &tank2;
        tankb = &tank1;
    }
    else
    {
        exit(-4);
    }
    int x, y;
    switch (tanka->shoot_dir)
    {
    case SHOOT_UP:
        x = tanka->x;
        y = tanka->y - 1;
        break;
    case SHOOT_DOWN:
        x = tanka->x;
        y = tanka->y + 1;
        break;
    case SHOOT_LEFT:
        x = tanka->x - 1;
        y = tanka->y;
        break;
    case SHOOT_RIGHT:
        x = tanka->x + 1;
        y = tanka->y;
        break;
    default:
        fprintf(stderr, "error: -4\n");
        exit(-4);
    }
    if (x < 0 || x > MAP_RANGE_X - 1)
        return;
    if (y < 0 || y > MAP_RANGE_Y - 1)
        return;
    switch (map[x][y])
    {
    case MAP_EMPTY:
        map[x][y] = MAP_BULLET;
        switch (tanka->shoot_dir)
        {
        case SHOOT_UP:
            bullet[x][y] = BULLET_UP;
            break;
        case SHOOT_DOWN:
            bullet[x][y] = BULLET_DOWN;
            break;
        case SHOOT_LEFT:
            bullet[x][y] = BULLET_LEFT;
            break;
        case SHOOT_RIGHT:
            bullet[x][y] = BULLET_RIGHT;
            break;
        default:
            exit(-4);
        }
        break;
    case MAP_TANK1:
        TakeDamage(&tank1,BULLET_DMG);
        break;
    case MAP_TANK2:
        TakeDamage(&tank2,BULLET_DMG);
        break;
    case MAP_BULLET:
        map[x][y] = MAP_BOOM;
        break;
    case MAP_BLOCK:
        break;
    case MAP_BOOM:
        break;
    default:
        fprintf(stderr, "error: -4\n");
        exit(-4);
    }
}

void TakeDamage(tank *tanka, int damage)
{
    tanka->HP -= damage;
    if (tanka->HP <= 0)
    {
        tanka->stat = EXPLODE;
    }
}