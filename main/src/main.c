#include "uart.h"
#include "joystick.h"
#include "motor.h"

#include "map.h"
#include "bullet.h"
#include "tank.h"
#include "game.h"


#include <stdlib.h>
#include <stdio.h>
void InitHareware();

void CN_handler()
{
    GameStart();
    while (!CheckGameStat())
    {
        GameRound();
        SendMap();
        DelayMsec(1000);
    }
    SendGameStat(CheckGameStat());
}

int main()
{
    InitHareware();
    while (1)
        ;
}
void InitHareware()
{
    // Initial joystick
    // Initial motor
    // Initial LCD
    initIntGlobal();
    UART_init();
    // Initial Change Notice
}
