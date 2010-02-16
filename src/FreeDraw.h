#ifndef FREEDRAW_H
#define FREEDRAW_H

#include <Allegro.h>
#include <vector>
#include <algorithm>

#include "MathUtils.h"
#include "World.h"
#include "Body.h"
#include "RenderUtils.h"
#include "GameUtils.h"

#define MINFIRSTDIST 10
#define MINCOS -0.98
#define CLOSEPOLYDIST 100

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
    Point first, last, least, great;
    vector<Point> points;

    void reset(void);
};

#endif // FREEDRAW_H
