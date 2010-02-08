#ifndef FREEDRAW_H
#define FREEDRAW_H

#define INF 0x3f3f3f3f

#include <Allegro.h>
#include <vector>
#include <algorithm>

#include "MathUtils.h"
#include "World.h"
#include "Body.h"
#include "RenderUtils.h"
#include "GameUtils.h"

class World;
using namespace std;

class FreeDraw
{
public:
    BITMAP *bmp;
    bool On;

    FreeDraw(void);
    ~FreeDraw(void);

    void takePoint(Point p);
    bool makeBody(World *world);

private:
    Point lastPoint, least, great;
    vector<Point> points;

    void reset(void);
};

#endif // FREEDRAW_H
