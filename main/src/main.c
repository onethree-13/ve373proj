#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "game.h"

#include "joystick.h"
#include "motor.h"
#include "uart.h"
#include <stdlib.h>
#include <stdio.h>
void InitHareware();

void CN_handler()
{
    GameStart();
    while (!CheckGameStat())
    {
        GameRound();
    }
    // Display info
}
//

int main()
{
    InitHareware();
    while (1)
        ;
}
void InitHareware()
{
    // Initial joystick;
    // Initial motor;
    // Initial LCD;
    // Initial Change Notice;
}
