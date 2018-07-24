#include <stdio.h>
#include "../../main/src/game.h"
#include "../../main/src/bullet.h"
#include "../../main/src/map.h"
#include "../../main/src/tank.h"

const char *GetMapName(enum MAP_STAT stat)
{
    switch (stat)
    {
    case MAP_EMPTY:
        return "0";
    case MAP_TANK1:
        return "TANK1";
    case MAP_TANK2:
        return "TANK2";
    case MAP_BULLET:
        return "BULLET";
    case MAP_BLOCK:
        return "BLOCK";
    case MAP_BOOM:
        return "BOOM";
    }
}

const char *GetGameStatName(enum GAME_STAT stat)
{
    switch (stat)
    {
    case RUNNING:
        return "RUNNING";
    case TANK1_WIN:
        return "TANK1_WIN";
    case TANK2_WIN:
        return "TANK2_WIN";
    case DRAW:
        return "DRAW";
    }
}

void display()
{
    int i, j;
    for (i = 0; i < MAP_RANGE_X; i++)
    {
        for (j = 0; j < MAP_RANGE_Y; j++)
            printf("%s\t", GetMapName(map[j][i]));
        printf("\n");
    }
}

int main()
{
    int tank1movedir, tank1shootdir, tank2movedir, tank2shootdir;
    GameStart();
    tank1.x = 3;
    tank1.y = 3;
    tank1.move_dir = MOVE_STATIC;
    tank1.shoot_dir = SHOOT_DOWN;
    tank1.stat = HEALTHY;
    map[0][0] = MAP_EMPTY;
    map[tank1.x][tank1.y] = MAP_TANK1;
    tank2.x = 6;
    tank2.y = 6;
    tank2.move_dir = MOVE_STATIC;
    tank2.shoot_dir = SHOOT_UP;
    tank2.stat = HEALTHY;
    map[MAP_RANGE_X - 1][MAP_RANGE_Y - 1] = MAP_EMPTY;
    map[tank2.x][tank2.y] = MAP_TANK2;
    printf("Game Initialize.\n");
    display();
    getchar();
    while (!CheckGameStat())
    {
        UpdateMapStat();
        printf("UpdateMapStat\n");
        display();
        getchar();
        printf("tank1.move.dir: UP 0, DOWN 1, LEFT 2, RIGHT 3, STATIC 4\n");
        scanf("%d", &tank1movedir);
        tank1.move_dir = tank1movedir;
        TankMove(1);
        printf("TankMove(1)\n");
        display();
        getchar();
        printf("tank2.move.dir: UP 0, DOWN 1, LEFT 2, RIGHT 3, STATIC 4\n");
        scanf("%d", &tank2movedir);
        tank2.move_dir = tank2movedir;
        TankMove(2);
        printf("TankMove(2)\n");
        display();
        getchar();
        printf("tank1.shoot.dir: UP 0, DOWN 1, LEFT 2, RIGHT 3\n");
        scanf("%d", &tank1shootdir);
        tank1.shoot_dir = tank1shootdir;
        TankShoot(1);
        printf("TankShoot(1)\n");
        display();
        getchar();
        printf("tank2.shoot.dir: UP 0, DOWN 1, LEFT 2, RIGHT 3\n");
        scanf("%d", &tank2shootdir);
        tank2.shoot_dir = tank2shootdir;
        TankShoot(2);
        printf("TankShoot(2)\n");
        display();
        getchar();
        UpdateBulletStat();
        printf("UpdateBulletStat:1\n");
        display();
        getchar();
        UpdateMapStat();
        printf("UpdateMapStat\n");
        display();
        getchar();
        UpdateBulletStat();
        printf("UpdateBulletStat:1\n");
        display();
        getchar();
    }
    printf("%s\n", GetGameStatName(CheckGameStat()));
}