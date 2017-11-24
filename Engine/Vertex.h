#pragma once

struct Position
{
	float X;
	float Y;
};

struct Color
{
	GLubyte R;
	GLubyte G;
	GLubyte B;
	GLubyte A;
};

struct UV
{
	float U;
	float V;
};

struct Vertex
{
	Position Position;

	Color Color;

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
};