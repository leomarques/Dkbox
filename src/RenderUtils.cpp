#include "RenderUtils.h"

BITMAP* createBoxBitmap(const b2Vec2 dimensions)
{
    BITMAP* bmp = makeBitmap((int) (dimensions.x * 2 * SCALE), (int) (dimensions.y * 2 * SCALE), TRANSPARENT);
    if (!bmp) return bmp;

    rect(bmp, 0, 0, bmp->w - 1, bmp->h - 1, GREEN);

    return bmp;
}

BITMAP* createCircleBitmap(const float32 radius, const int color)
{
    BITMAP* bmp = makeBitmap((int) (radius * 2 * SCALE) + 1, (int) (radius * 2 * SCALE) + 1, TRANSPARENT);
    if (!bmp) return bmp;

    circle(bmp, (int) (radius * SCALE), (int) (radius * SCALE), (int) (radius * SCALE), color);
    line(bmp, bmp->w / 2, bmp->h / 2, bmp->w / 2, 0, color);

    return bmp;
}
