#include "Dynamic.h"
#include "GameConstants.h"

// Constructors, using the GameObject constructors
Dynamic::Dynamic(Texture* t_texture_to_use) : GameObject(t_texture_to_use)
{
}

Dynamic::Dynamic(Texture* t_texture_to_use, const glm::vec2 t_new_position) : GameObject(t_texture_to_use, t_new_position)
{
}

Dynamic::Dynamic(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth) : GameObject(t_texture_to_use, t_new_position, t_new_depth)
{
}

Dynamic::Dynamic(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation) : GameObject(
	t_texture_to_use, t_new_position, t_new_rotation)
{
}

Dynamic::~Dynamic()
{
}

// Get the current value of the object velocity
glm::vec2 Dynamic::GetVelocity() const
{
	return this->velocity;
}

// Get the current value of the object acceleration
glm::vec2 Dynamic::GetAcceleration() const
{
	return acceleration;
}

// Set the current value of the object velocity
void Dynamic::SetVelocity(const glm::vec2 t_new_velocity)
{
	this->velocity = t_new_velocity;
}


// Set the current value of the object acceleration
void Dynamic::SetAcceleration(const glm::vec2 t_new_acceleration)
{
	this->acceleration = t_new_acceleration;
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
