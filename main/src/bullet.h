#ifndef _BULLET_H_
#define _BULLET_H_

enum DIRECTION
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

struct bullet
{
    int x, y;
    int direction;
}
#endif