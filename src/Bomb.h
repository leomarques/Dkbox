#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include <Box2D.h>

#define EXPLOSION 1.3f
#define FUSETIME 120  // 1 second = 60.

class Bomb
{
    void blowUp(void) const;

    b2Body *bBody;
    b2World *bWorld;
    int fuse;

public:
    Bomb(b2Body *body, b2World *world);
    bool checkFuse(void);

    inline b2Body* GetBody(void)
    {
        return bBody;
    }
};

#endif // BOMB_H_INCLUDED
