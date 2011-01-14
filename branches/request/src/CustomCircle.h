#ifndef CUSTOMCIRCLE_H
#define CUSTOMCIRCLE_H

#include <allegro.h>

#include "MathUtils.h"
#include "World.h"
#include "Body.h"
#include "RenderUtils.h"
#include "GameUtils.h"

class CustomCircle
{
public:
    BITMAP *bmp;
    bool On;

    CustomCircle(void);
    ~CustomCircle(void);

    void takePoint(Point p);
    bool makeBody(World *world);

private:
    Point p1, p2;

    void reset(void);
    float32 cleanSize(float32 f);
};

#endif // CUSTOMCIRCLE_H
