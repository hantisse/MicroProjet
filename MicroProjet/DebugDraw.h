#include <Box2D/Box2D.h>
#include <iostream>

class DebugDraw : public b2Draw
{
public:

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) { std::cout << "polygon" << std::endl; };
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) { std::cout << "circle" << std::endl; };
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) { std::cout << "colidcircle" << std::endl; };
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) { std::cout << "segment" << std::endl; };
	virtual void DrawTransform(const b2Transform& xf) { std::cout << "transform" << std::endl; };
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) { std::cout << "point" << std::endl; };
};