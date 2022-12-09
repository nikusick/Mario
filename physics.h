#ifndef PHYSICS
#define PHYSICS

#include <box2d/box2d.h>

class DebugDraw : public b2Draw { // b2Draw has all the virtual functions that we need to override here
public:
    // We won't be implementing all of these, but if we don't declare them here we'll get an override error
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawTransform(const b2Transform& xf);
};

#endif
