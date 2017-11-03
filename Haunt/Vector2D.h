#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#include "GameConstants.h";

typedef struct Vector2D
{
	float  X;
	float  Y;

	// Get the dot product of two 2D vectors
	static int dotProduct(Vector2D vector1, Vector2D vector2)
	{
		return ((vector1.X * vector2.X) + (vector1.Y * vector2.Y));
	}

	// Get the andgle between two 2D vectors
	static float getAngle(Vector2D vector1, Vector2D vector2)
	{
		int dotProduct = Vector2D::dotProduct(vector1, vector2);

		float cos = dotProduct / (vector1.getLength() * vector2.getLength());

		return acos(cos);
	}

	// Get the length of the current 2D vector
	float getLength()
	{
		return sqrt((X * X) + (Y * Y));
	}

	Vector2D operator +(const Vector2D other)
	{
		Vector2D newVector;
		newVector.X = this->X + other.X;
		newVector.Y = this->Y + other.Y;

		return newVector;
	}

	Vector2D operator -(const Vector2D other)
	{
		Vector2D newVector;
		newVector.X = this->X - other.X;
		newVector.Y = this->Y - other.Y;

		return newVector;
	}

	Vector2D operator *(const float other)
	{
		Vector2D newVector;
		newVector.X = this->X * other;
		newVector.Y = this->Y * other;

		return newVector;
	}

	Vector2D operator /(const float other)
	{
		Vector2D newVector;
		newVector.X = this->X / other;
		newVector.Y = this->Y / other;

		return newVector;
	}
};

// Found solution on stack overflow, thanks to user 616700/erik
inline std::ostream& operator<<(std::ostream& string, Vector2D const& vectorToOutput)
{
	string << "[ " << vectorToOutput.X << "; " << vectorToOutput.Y << " ]" << endl;
	return string;
}

#endif // !_VECTOR2D_H