#include "FreeDraw.h"

FreeDraw::FreeDraw(void)
{
    On = false;
    bmp = makeBitmap(SCREEN_W, SCREEN_H, TRANSPARENT);
    if (!bmp)
        exit(-2);
    reset();
}

FreeDraw::~FreeDraw(void)
{
    destroy_bitmap(bmp);
}

void FreeDraw::takePoint(Point p)
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

    drawLine(bmp, p, last, GREEN);
    last = p;

    if (pointDistance(p, points.back()) < MINFIRSTDIST)
        return;

    if (points.size() == 1)
    {
        points.push_back(p);
        return;
    }

    Point p0 = points[(int) points.size() - 2] - points.back();
    Point p1 = p - points.back();

    if (vecsCos(p0, p1) < MINCOS)
        points.pop_back();

    points.push_back(p);
}

void FreeDraw::reset(void)
{
    least.x = INF;
    least.y = INF;
    great.x = -INF;
    great.y = -INF;

    points.clear();
    clear_to_color(bmp, TRANSPARENT);
}

bool FreeDraw::makeBody(World *world)
{
    On = false;

    if ((int) points.size() < 3 || pointDistance(first, last) > CLOSEPOLYDIST)
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
            blit(bmp, bodyBmp, least.x, least.y, 0, 0, w, h);
        }
        else
        {
            bodyBmp = makeBitmap(l * 2, d * 2, TRANSPARENT);
            blit(bmp, bodyBmp, least.x, least.y, 0, (bodyBmp->h / 2) - (com.y - least.y), w, h);
        }
    }
    else
    {
        if (u >= d)
        {
            bodyBmp = makeBitmap(r * 2, u * 2, TRANSPARENT);
            blit(bmp, bodyBmp, least.x, least.y, (bodyBmp->w / 2) - (com.x - least.x), 0, w, h);
        }
        else
        {
            bodyBmp = makeBitmap(r * 2, d * 2, TRANSPARENT);
            blit(bmp, bodyBmp, least.x, least.y, (bodyBmp->w / 2) - (com.x - least.x), (bodyBmp->h / 2) - (com.y - least.y), w, h);
        }
    }

    b->bmp = bodyBmp;

    reset();

    return true;
}
