#include "CustomPolygon.h"

CustomPolygon::CustomPolygon()
{
    On = false;
    bmp = makeBitmap(SCREEN_W, SCREEN_H, TRANSPARENT);
    bmp1 = makeBitmap(SCREEN_W, SCREEN_H, TRANSPARENT);
    reset();
}

CustomPolygon::~CustomPolygon()
{
    destroy_bitmap(bmp);
    destroy_bitmap(bmp1);
}

void CustomPolygon::takePoint(Point p)
{
    On = true;

    least.x = min(least.x, p.x);
    least.y = min(least.y, p.y);
    great.x = max(great.x, p.x);
    great.y = max(great.y, p.y);

    if (points.empty())
    {
        points.push_back(p);
        first = p;
        last = first;
        return;
    }

    drawLine(bmp1, p, last, GREEN);
    last = p;

    points.push_back(p);
}

void CustomPolygon::updateView(Point p)
{
    clear_to_color(bmp, TRANSPARENT);
    blit(bmp1, bmp, 0, 0, 0, 0, bmp->w, bmp->h);

    drawLine(bmp, points.back(), p, GREEN);
}

void CustomPolygon::reset(void)
{
    least.x = INF;
    least.y = INF;
    great.x = -INF;
    great.y = -INF;

    points.clear();
    clear_to_color(bmp, TRANSPARENT);
    clear_to_color(bmp1, TRANSPARENT);
}

bool CustomPolygon::makeBody(World *world)
{
    On = false;

    if ((int) points.size() < 3)
    {
        reset();
        return false;
    }

    Body *b = world->makeBody(points);

    if (!b)
    {
        reset();
        return false;
    }

    drawLine(bmp1, last, first, GREEN);

    Point com = b->getAllegPosition();

    int l = com.x - least.x, r = great.x - com.x,
    u = com.y - least.y, d = great.y - com.y,
    w = great.x - least.x, h = great.y - least.y;

    l++; r++; u++; d++; w++; h++;

    BITMAP *bodyBmp;

    if (l >= r)
    {
        if (u >= d)
        {
            bodyBmp = makeBitmap(l * 2, u * 2, TRANSPARENT);
            blit(bmp1, bodyBmp, least.x, least.y, 0, 0, w, h);
        }
        else
        {
            bodyBmp = makeBitmap(l * 2, d * 2, TRANSPARENT);
            blit(bmp1, bodyBmp, least.x, least.y, 0, (bodyBmp->h / 2) - (com.y - least.y), w, h);
        }
    }
    else
    {
        if (u >= d)
        {
            bodyBmp = makeBitmap(r * 2, u * 2, TRANSPARENT);
            blit(bmp1, bodyBmp, least.x, least.y, (bodyBmp->w / 2) - (com.x - least.x), 0, w, h);
        }
        else
        {
            bodyBmp = makeBitmap(r * 2, d * 2, TRANSPARENT);
            blit(bmp1, bodyBmp, least.x, least.y, (bodyBmp->w / 2) - (com.x - least.x), (bodyBmp->h / 2) - (com.y - least.y), w, h);
        }
    }

    b->bmp = bodyBmp;

    reset();

    return true;
}
