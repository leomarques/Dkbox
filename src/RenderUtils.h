#ifndef RENDERUTILS_H_INCLUDED
#define RENDERUTILS_H_INCLUDED

#include <Allegro.h>
#include <Box2D.h>
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

#define SCALE 60.0f

BITMAP* createBoxBitmap(const b2Vec2 dimensions);
BITMAP* createCircleBitmap(const float32 radius, const int color);

inline void drawLine(BITMAP *bmp, Point p0, Point p1, int color)
{
    line(bmp, p0.x, p0.y, p1.x, p1.y, color);
}

inline void drawCircle(BITMAP *bmp, Point p, int radius, int color)
{
    circle(bmp, p.x, p.y, radius, color);
}

#endif // RENDERUTILS_H_INCLUDED
