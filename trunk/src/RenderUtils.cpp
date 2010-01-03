#include "RenderUtils.h"

BITMAP* createBoxBitmap(const b2Vec2 dimensions)
{
    BITMAP* bmp = create_bitmap((int) (dimensions.x * 2 * SCALE), (int) (dimensions.y * 2 * SCALE));
    if (!bmp) return bmp;

    clear_to_color(bmp, TRANSPARENT);
    rect(bmp, 0, 0, bmp->w - 1, bmp->h - 1, GREEN);

    return bmp;
}

BITMAP* createCircleBitmap(const float32 radius, const int color)
{
    BITMAP* bmp = create_bitmap((int) (radius * 2 * SCALE) + 1, (int) (radius * 2 * SCALE) + 1);
    if (!bmp) return bmp;

    clear_to_color(bmp, TRANSPARENT);
    circle(bmp, (int) (radius * SCALE), (int) (radius * SCALE), (int) (radius * SCALE), color);
    line(bmp, bmp->w / 2, bmp->h / 2, bmp->w / 2, 0, color);

    return bmp;
}
