#include "DebugDraw.h"

DebugDraw::DebugDraw(BITMAP *_bmp)
{
    bmp = _bmp;
    uint32 flags = 0;

    flags += b2DebugDraw::e_shapeBit;
    flags += b2DebugDraw::e_coreShapeBit;
    //flags += b2DebugDraw::e_jointBit;
	//flags += b2DebugDraw::e_aabbBit;
	//flags += b2DebugDraw::e_obbBit;
	//flags += b2DebugDraw::e_pairBit;
	//flags += b2DebugDraw::e_centerOfMassBit;

    SetFlags(flags);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    for (int32 i = 1; i < vertexCount; i++)
    {
        drawLine(bmp, coordB2ToAlleg(vertices[i]), coordB2ToAlleg(vertices[i - 1]), BLUE);
        drawCircle(bmp, coordB2ToAlleg(vertices[i]), 3, BLUE);
    }

    drawLine(bmp, coordB2ToAlleg(vertices[vertexCount - 1]), coordB2ToAlleg(vertices[0]), BLUE);
    drawCircle(bmp, coordB2ToAlleg(vertices[0]), 3, BLUE);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    drawCircle(bmp, coordB2ToAlleg(center), (int) (radius * SCALE), BLUE);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    drawLine(bmp, coordB2ToAlleg(p1), coordB2ToAlleg(p2), BLUE);
}

void DebugDraw::DrawXForm(const b2XForm& xf){}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){}
