#ifndef GAMEUTILS_H_INCLUDED
#define GAMEUTILS_H_INCLUDED

#include <Box2D.h>
#include <Allegro.h>

#define RED makecol(255, 0, 0)
#define GREEN makecol(0, 255, 0)
#define BLUE makecol(0, 0, 255)
#define YELLOW makecol(255, 255, 0)
#define PURPLE makecol(225, 0, 220)
#define WHITE makecol(255, 255, 255)
#define GRAY makecol(180, 180, 180)
#define TRANSPARENT makecol(255, 0, 255)

#define RANDOM(f, l) (rand() % (l - f + 1) + f)
#define SCALE 60.0f

//extern const float32 SCALE;
extern const float32 timeStep;
extern const int iterations;

inline b2Vec2 coordAllegToB2(int x, int y)
{
    return b2Vec2((x - (SCREEN_W / 2)) / SCALE, - (y - SCREEN_H) / SCALE);
}

#endif // GAMEUTILS_H_INCLUDED
