#ifndef DEBUGDRAW_H_INCLUDED
#define DEBUGDRAW_H_INCLUDED

#include <Box2D.h>
#include <allegro.h>

#include "RenderUtils.h"
#include "GameUtils.h"

class DebugDraw : public b2DebugDraw
{
    BITMAP *bmp;
public:
    DebugDraw(BITMAP *_bmp);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawXForm(const b2XForm& xf);
};

#endif // DEBUGDRAW_H_INCLUDED
