#ifndef GAMEUTILS_H_INCLUDED
#define GAMEUTILS_H_INCLUDED

#include <Allegro.h>
#include <cmath>
#include <time.h>

#include "RenderUtils.h"
#include "MathUtils.h"

#define RANDOM(f, l) (rand() % (l - f + 1) + f)

inline float32 coordXAllegToB2(int x)
{
    return (x - (SCREEN_W / 2)) / SCALE;
}

inline float32 coordYAllegToB2(int y)
{
    return - (y - SCREEN_H) / SCALE;
}

inline b2Vec2 coordAllegToB2(Point p)
{
    return b2Vec2(coordXAllegToB2(p.x), coordYAllegToB2(p.y));
}

inline int coordXB2ToAlleg(float32 x)
{
    return (int) (x * SCALE + (SCREEN_W / 2));
}

inline int coordYB2ToAlleg(float32 y)
{
    return (int) (- y * SCALE + SCREEN_H);
}

inline Point coordB2ToAlleg(b2Vec2 p)
{
    return Point(coordXB2ToAlleg(p.x), coordYB2ToAlleg(p.y));
}

#endif // GAMEUTILS_H_INCLUDED
