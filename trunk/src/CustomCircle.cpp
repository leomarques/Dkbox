#include "CustomCircle.h"

CustomCircle::CustomCircle(void)
{
    On = false;
    bmp = makeBitmap(SCREEN_W, SCREEN_H, TRANSPARENT);
    reset();
}

CustomCircle::~CustomCircle(void)
{
    destroy_bitmap(bmp);
}

void CustomCircle::takePoint(Point p)
{
    p2.x = p.x;
    p2.y = p.y;

    if (!On)
    {
        On = true;
        p1.x = p.x;
        p1.y = p.y;
    }

    clear_to_color(bmp, TRANSPARENT);
    drawCircle(bmp, p1, pointDistance(p1, p2), GREEN);
}

void CustomCircle::reset(void)
{
    On = false;
    clear_to_color(bmp, TRANSPARENT);
}

inline float32 CustomCircle::cleanSize(float32 f)
{
    if (f < 0.0f)
        f = -f;
    if (f < 0.1f)
        f = 0.1f;
    return f;
}

bool CustomCircle::makeBody(World *world)
{
    b2Vec2 c1 = coordAllegToB2(p1);
    b2Vec2 c2 = coordAllegToB2(p2);

    float32 radius = cleanSize(pointDistance(p1, p2) / SCALE);
    Body *b = world->makeCircle(c1, radius);

    if (!b)
    {
        reset();
        return false;
    }

    b->bmp = createCircleBitmap(radius, RANDOMCOLOR);

    reset();

    return true;
}
