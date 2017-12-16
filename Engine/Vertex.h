#pragma once

// The position structure for the vertex (8 bytes)
struct Position
{
	// 32 bits
	GLfloat X;
	// 32 bits
	GLfloat Y;
};

// The color structure (4 bytes)
struct Color
{
	Color() : R(255), G(255), B(255), A(255)
	{
	}
	Color(GLubyte t_new_r, GLubyte t_new_g, GLubyte t_new_b, GLubyte t_new_a) : R(t_new_r), G(t_new_g), B(t_new_b), A(t_new_a)
	{
	}

	// Byte x 4
	GLubyte R;
	GLubyte G;
	GLubyte B;
	GLubyte A;
};

// The UV coordinates of a vertex (8 bytes)
struct UV
{
	// 32 bits x 2
	GLfloat U;
	GLfloat V;
};

// The vertex structure (24 bytes) + padding of 8 bytes
struct Vertex
{
	// 4 bytes
	Color Color;
	// 4 bytes
	GLfloat Depth = 1;
	// 8 bytes
	Position Position;
	// 8 bytes
	UV UVCoordinates;
	

	void SetPosition(float t_new_x, float t_new_y)
	{
		Position.X = t_new_x;
		Position.Y = t_new_y;
	}

	void SetColor(GLubyte t_new_r, GLubyte t_new_g, GLubyte t_new_b, GLubyte t_new_a)
	{
		Color.R = t_new_r;
		Color.G = t_new_g;
		Color.B = t_new_b;
		Color.A = t_new_a;
	}

	void SetUV(float t_new_u, float t_new_v)
	{
		UVCoordinates.U = t_new_u;
		UVCoordinates.V = t_new_v;
	}

	void SetDepth(float t_new_depth)
	{
		Depth = t_new_depth;
	}
private:
	// 12 bytes padding
	GLfloat padding[2];
};