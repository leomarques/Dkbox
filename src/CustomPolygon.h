#ifndef CUSTOMPOLYGON_H
#define CUSTOMPOLYGON_H

#include <allegro.h>
#include <vector>
#include <algorithm>

#include "MathUtils.h"
#include "World.h"
#include "Body.h"
#include "RenderUtils.h"
#include "GameUtils.h"

class World;
using namespace std;

class CustomPolygon
{
public:
    BITMAP *bmp, *bmp1;
    bool On;

    CustomPolygon(void);
    ~CustomPolygon(void);

    void takePoint(Point p);
    void updateView(Point p);
    bool makeBody(World *world);

private:
    Point first, last, least, great;
    vector<Point> points;

    void reset(void);
};

#endif // CUSTOMPOLYGON_H
