#ifndef _VECTOR2D_H
#define _VECTOR2D_H


#include "GameConstants.h";

struct Vector2D
{
	float X;
	float Y;

	Vector2D()
	{
		this->X = 0;
		this->Y = 0;
	}

	Vector2D(const double t_new_x, const double t_new_y)
	{
		this->X = t_new_x;
		this->Y = t_new_y;
	}

	// Get the dot product of two 2D vectors
	static int DotProduct(const Vector2D t_vector1, const Vector2D t_vector2)
	{
		return ((t_vector1.X * t_vector2.X) + (t_vector1.Y * t_vector2.Y));
	}

	// Get the andgle between two 2D vectors
	static float GetAngle(Vector2D t_vector1, Vector2D t_vector2)
	{
		const int dotProduct = Vector2D::DotProduct(t_vector1, t_vector2);

		const float cos = dotProduct / (t_vector1.GetLength() * t_vector2.GetLength());

		return acos(cos);
	}

	static Vector2D Lerp(const Vector2D t_vector1, const Vector2D t_vector2, const double t)
	{
		return (t_vector1 * (1 - t)) + (t_vector2 * t);
	}

	// Get the length of the current 2D vector
	float GetLength() const
	{
		return sqrt((X * X) + (Y * Y));
	}

	Vector2D operator +(const Vector2D t_other) const
	{
		Vector2D newVector;
		newVector.X = this->X + t_other.X;
		newVector.Y = this->Y + t_other.Y;

		return newVector;
	}

	Vector2D operator -(const Vector2D t_other) const
	{
		Vector2D newVector;
		newVector.X = this->X - t_other.X;
		newVector.Y = this->Y - t_other.Y;

		return newVector;
	}

	Vector2D operator *(const float t_other) const
	{
		Vector2D newVector;
		newVector.X = this->X * t_other;
		newVector.Y = this->Y * t_other;

		return newVector;
	}

	Vector2D operator /(const float t_other) const
	{
		Vector2D newVector;
		newVector.X = this->X / t_other;
		newVector.Y = this->Y / t_other;

		return newVector;
	}

	static int CompareX(const Vector2D t_first_vector, const Vector2D t_second_vector)
	{
		if (t_first_vector.X < t_second_vector.X)
		{
			return -1;
		}
		else if (t_first_vector.X > t_second_vector.X)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

// Found solution on stack overflow, thanks to user 616700/erik
inline ostream& operator<<(ostream& t_string, Vector2D const& t_vector_to_output)
{
	t_string << "[ " << t_vector_to_output.X << "; " << t_vector_to_output.Y << " ]" << endl;
	return t_string;
}

#endif // !_VECTOR2D_H
