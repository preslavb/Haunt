#include "Dynamic.h"
#include "GameConstants.h"

// Constructors, using the GameObject constructors
Dynamic::Dynamic(Texture* t_texture_to_use) : GameObject(t_texture_to_use)
{
	type = "Dynamic";
}

Dynamic::Dynamic(Texture* t_texture_to_use, const glm::vec2 t_new_position) : GameObject(t_texture_to_use, t_new_position)
{
	type = "Dynamic";
}

Dynamic::Dynamic(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth) : GameObject(t_texture_to_use, t_new_position, t_new_depth)
{
	type = "Dynamic";
}

Dynamic::Dynamic(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation) : GameObject(
	t_texture_to_use, t_new_position, t_new_rotation)
{
	type = "Dynamic";
}

Dynamic::~Dynamic()
{
}

// Update physics logic
void Dynamic::Update(const float t_delta_time)
{
	// If the object has fallen to the floor, stop it's vertical motion
	if (this->GetPosition().y > 600)
	{
		this->SetPosition(glm::vec2(this->GetPosition().x, 600));
		grounded = true;
	}

	// If the object is in the air, apply gravity to the velocity
	if (!grounded)
	{
		this->velocity.y += _GRAVITY * _METER * t_delta_time;
	}
	else
	{
		this->velocity.y = 0;
	}

	// Move the object each frame by the velocity value
	this->Move(this->velocity * _METER * t_delta_time);
}

void Dynamic::Move(const glm::vec2 t_offset)
{
	// Offset the object by the specified std::vec2
	this->SetPosition(this->GetPosition() + t_offset);
}
