#include "pch.h"
#include <Box2D/Box2D.h>
#include "glfw/glfw3.h"
#include "DebugDraw.h"

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	//set up vertex array
	GLfloat glverts[16]; //allow for polygons up to 8 vertices
	glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
	glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

	//fill in vertex positions as directed by Box2D
	for (int i = 0; i < vertexCount; i++) {
		glverts[i * 2] = vertices[i].x;
		glverts[i * 2 + 1] = vertices[i].y;
	}

	//draw solid area
	glColor4f(color.r, color.g, color.b, 1);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	//draw lines
	glLineWidth(3); //fat lines
	glColor4f(1, 0, 1, 1); //purple
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}