#ifndef GAMEUTILS_H_INCLUDED
#define GAMEUTILS_H_INCLUDED

#include <Allegro.h>
#include "RenderUtils.h"
#include "MathUtils.h"
#include <math.h>

#define RANDOM(f, l) (rand() % (l - f + 1) + f)

inline b2Vec2 coordAllegToB2(int x, int y)
{
    return b2Vec2((x - (SCREEN_W / 2)) / SCALE, - (y - SCREEN_H) / SCALE);
}

inline int coordXB2ToAlleg(float32 x)
{
    return (int) round(x * SCALE + (SCREEN_W / 2));
}

inline int coordYB2ToAlleg(float32 y)
{
    return (int) round(- y * SCALE + SCREEN_H);
}

inline Point coordB2ToAlleg(b2Vec2 p)
{
    return Point(coordXB2ToAlleg(p.x), coordYB2ToAlleg(p.y));
}

#endif // GAMEUTILS_H_INCLUDED
