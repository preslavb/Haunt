#pragma once
#include <glm/detail/type_vec2.hpp>

struct Rect
{
private:
	glm::vec2 position;
	glm::vec2 dimensions;
public:
	Rect(glm::vec2 t_new_position, glm::vec2 t_new_dimensions) : position(t_new_position), dimensions(t_new_dimensions)
	{
	}

	glm::vec2 TopLeft()
	{
		return position;
	}

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

	glm::vec2 GetPosition()
	{
		return position;
	}

	glm::vec2 GetDimensions()
	{
		return dimensions;
	}

	void SetPosition(glm::vec2 t_new_position)
	{
		position = t_new_position;
	}
};
