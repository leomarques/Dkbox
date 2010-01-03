#ifndef MATHUTILS_H_INCLUDED
#define MATHUTILS_H_INCLUDED

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

    void operator=(Point p)
    {
        x = p.x;
        y = p.y;
    }
};

#endif // MATHUTILS_H_INCLUDED
