#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>

struct _controllable{};

struct movement{
    float acc;
    float max_speed;
    float jump_height;
};

struct _moving_left{};
struct _moving_right{};
struct _jump{};

#endif // MOVEMENT_H_
