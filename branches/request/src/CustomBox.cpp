#include "CustomBox.h"

CustomBox::CustomBox(void)
{
    On = false;
    bmp = makeBitmap(SCREEN_W, SCREEN_H, TRANSPARENT);
    reset();
}

CustomBox::~CustomBox(void)
{
    destroy_bitmap(bmp);
}

void CustomBox::takePoint(Point p)
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
    drawRect(bmp, p1, p2, GREEN);
}

void CustomBox::reset(void)
{
    On = false;
    clear_to_color(bmp, TRANSPARENT);
}

inline float32 CustomBox::cleanSize(float32 f)
{
    if (f < 0.0f)
        f = -f;
    if (f < 0.1f)
        f = 0.1f;
    return f;
}

bool CustomBox::makeBody(World *world)
{
    b2Vec2 c1 = coordAllegToB2(p1);
    b2Vec2 c2 = coordAllegToB2(p2);

    b2Vec2 dimensions(cleanSize(c2.x - c1.x) / 2.0f, cleanSize(c2.y - c1.y) / 2.0f);

    Body *b = world->makeBox(b2Vec2(c1.x + (c2.x - c1.x) / 2.0f, c1.y + (c2.y - c1.y) / 2.0f), dimensions);

    if (!b)
    {
        reset();
        return false;
    }

    b->bmp = createBoxBitmap(dimensions, RANDOMCOLOR);

    reset();

    return true;
}
