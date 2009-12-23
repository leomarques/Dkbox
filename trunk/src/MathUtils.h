#ifndef MATHUTILS_H_INCLUDED
#define MATHUTILS_H_INCLUDED

#include "math.h"

class Point
{
public:
    int x, y;

    Point()
    {
        x = y = 0;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator=(Point p)
    {
        x = p.x;
        y = p.y;

        return true;
    }
};

inline double pointDistance(Point p0, Point p1)
{
    return round(sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2)));
}

#endif // MATHUTILS_H_INCLUDED
