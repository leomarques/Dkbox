#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <Box2D.h>
#include <Allegro.h>

class Body
{
public:
    b2Body *body;
    b2World *world;
    BITMAP *bmp;
    bool markedForDeletion, isBomb;

    Body(b2Body *body, b2World *world, BITMAP *bmp)
    {
        this->body = body;
        body->SetUserData(this);
        this->world = world;
        this->bmp = bmp;
        markedForDeletion = false;
        isBomb = false;
    }

    ~Body(void)
    {
        destroy_bitmap(bmp);
        world->DestroyBody(body);
    }

    bool operator==(Body *b)
    {
        return body == b->body;
    }
};

#endif // BODY_H_INCLUDED
