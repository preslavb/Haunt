#ifndef _SPRITE_H
#define _SPRITE_H

#include <Windows.h>

#include <GL/glew.h>
#include "Vertex.h"
#include "GLSLProgram.h"

// The 2D representation of a texture in the game
class Sprite
{
public:
	Sprite();
	~Sprite();

	void Initialize(float t_x, float t_y, float t_width, float t_height);

	void Render();

private:
	float x;
	float y;
	float width;
	float height;
	GLuint vertexBuffer;
	GLSLProgram shaderProgram;
};
#endif
