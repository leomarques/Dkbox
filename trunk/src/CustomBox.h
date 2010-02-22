#ifndef CUSTOMBOX_H
#define CUSTOMBOX_H

#include <Allegro.h>

#include "MathUtils.h"
#include "World.h"
#include "Body.h"
#include "RenderUtils.h"
#include "GameUtils.h"

class CustomBox
{
public:
    BITMAP *bmp;
    bool On;

    CustomBox(void);
    ~CustomBox(void);

    void takePoint(Point p);
    bool makeBody(World *world);

private:
    Point p1, p2;

    void reset(void);
    float32 cleanSize(float32 f);
};

#endif // CUSTOMBOX_H
