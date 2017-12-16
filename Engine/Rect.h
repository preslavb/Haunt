#pragma once
#include <glm/detail/type_vec2.hpp>

// Structure for storing a rectangle
struct Rect
{
private:
	// The position and origin point of the rectangle
	glm::vec2 position;
	// The dimensions of the rectangle from the origin point
	glm::vec2 dimensions;
public:
	// Constructor and destructor
	Rect(glm::vec2 t_new_position, glm::vec2 t_new_dimensions) : position(t_new_position), dimensions(t_new_dimensions)
	{
	}

	Rect(float t_new_x, float t_new_y, float t_new_width, float t_new_height) : position(glm::vec2(t_new_x, t_new_y)), dimensions(glm::vec2(t_new_width, t_new_height))
	{
	}

	// Set the top left, which is also the origin point
	glm::vec2 TopLeft()
	{
		return position;
	}

	// Set the other corners of the rectangle
	glm::vec2 TopRight()
	{
		return glm::vec2(position.x + dimensions.x, position.y);
	}

	glm::vec2 BottomRight()
	{
		return glm::vec2(position.x + dimensions.x, position.y + dimensions.y);
	}

	glm::vec2 BottomLeft()
	{
		return glm::vec2(position.x, position.y + dimensions.y);
	}

	// Get the position of the rectangle (same as the top left)
	glm::vec2 GetPosition()
	{
		return position;
	}

	// Get the 2d dimensions of the rectangle
	glm::vec2 GetDimensions()
	{
		return dimensions;
	}

	// Set the position to the given one
	void SetPosition(glm::vec2 t_new_position)
	{
		position = t_new_position;
	}

	bool IsValid()
	{
		// If the width and height of the rectangle are not 0, then it is a valid rectangle and not a line or point
		return dimensions.x && dimensions.y;
	}
};
