#include <cstddef>
#include "Sprite.h"

Sprite::Sprite()
{
	vertexBuffer = 0;
}

Sprite::~Sprite()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
}

void Sprite::Initialize(float t_x, float t_y, float t_width, float t_height)
{
	x = t_x;
	y = t_y;
	width = t_width;
	height = t_height;

	if (!vertexBuffer)
	{
		glGenBuffers(1, &vertexBuffer);
	}

	Vertex vertexData[6];

	// First Tri
	vertexData[0].SetPosition(x + width, y + height);
	vertexData[0].SetUV(1, 1);

	vertexData[1].SetPosition(x, y + height);
	vertexData[1].SetUV(0, 1);

	vertexData[2].SetPosition(x + width, y);
	vertexData[2].SetUV(1, 0);

	// Second Tri
	vertexData[3].SetPosition(x, y);
	vertexData[3].SetUV(0, 0);

	vertexData[4].SetPosition(x + width, y);
	vertexData[4].SetUV(1, 0);

	vertexData[5].SetPosition(x , y + height);
	vertexData[5].SetUV(0, 1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, Color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, UVCoordinates));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
