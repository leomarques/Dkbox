#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include <Box2D.h>
#include <Allegro.h>

#include "Body.h"

#define EXPLOSION 1.3f
#define FUSETIME 120

class Bomb : public Body
{
public:
    Bomb(b2Body *body, BITMAP *bmp);
    ~Bomb(void);

    void checkFuse(void);

    bool operator==(Bomb *b)
    {
        return body == b->body;
    }

private:
    void blowUp(void);

    int fuse;
};

#endif // BOMB_H_INCLUDED
