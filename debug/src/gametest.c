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
    printf("Game Initialize.\n");
    display();
    getchar();
    while (CheckGameStat())
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
}