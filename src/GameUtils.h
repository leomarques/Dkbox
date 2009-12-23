#ifndef GAMEUTILS_H_INCLUDED
#define GAMEUTILS_H_INCLUDED

#include <Box2D.h>
#include <Allegro.h>
#include <math.h>
#include "MathUtils.h"

#define RED makecol(255, 0, 0)
#define GREEN makecol(0, 255, 0)
#define BLUE makecol(0, 0, 255)
#define YELLOW makecol(255, 255, 0)
#define PURPLE makecol(225, 0, 220)
#define LPURPLE makecol(165, 0, 220)
#define WHITE makecol(255, 255, 255)
#define GRAY makecol(180, 180, 180)
#define TRANSPARENT makecol(255, 0, 255)

#define RANDOM(f, l) (rand() % (l - f + 1) + f)
#define SCALE 60.0f

//extern float32 SCALE;
extern const float32 timeStep;
extern const int iterations;

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
    return (int) round(- y * SCALE + SCREEN_H );
}

inline Point coordB2ToAlleg(b2Vec2 p)
{
    return Point(coordXB2ToAlleg(p.x), coordYB2ToAlleg(p.y));
}

#endif // GAMEUTILS_H_INCLUDED
