#include "Dynamic.h"

// Constructors, using the GameObject constructors
Dynamic::Dynamic(Texture* t_texture_to_use) : GameObject(t_texture_to_use)
{
}

Dynamic::Dynamic(Texture* t_texture_to_use, const Vector2D t_new_position) : GameObject(t_texture_to_use, t_new_position)
{
}

Dynamic::Dynamic(Texture* t_texture_to_use, const Vector2D t_new_position, const float t_new_rotation) : GameObject(
	t_texture_to_use, t_new_position, t_new_rotation)
{
}

Dynamic::~Dynamic()
{
}

// Get the current value of the object velocity
Vector2D Dynamic::GetVelocity() const
{
	return this->velocity;
}

// Get the current value of the object acceleration
Vector2D Dynamic::GetAcceleration() const
{
	return acceleration;
}

// Set the current value of the object velocity
void Dynamic::SetVelocity(const Vector2D t_new_velocity)
{
	this->velocity = t_new_velocity;
}


// Set the current value of the object acceleration
void Dynamic::SetAcceleration(const Vector2D t_new_acceleration)
{
	this->acceleration = t_new_acceleration;
}

// Update physics logic
void Dynamic::Update(const float t_delta_time)
{
	// If the object has fallen to the floor, stop it's vertical motion
	if (this->GetPosition().Y > 600)
	{
		this->SetPosition(Vector2D(this->GetPosition().X, 600));
		grounded = true;
	}

	// If the object is in the air, apply gravity to the velocity
	if (!grounded)
	{
		this->velocity.Y += _GRAVITY * _METER * t_delta_time;
	}
	else
	{
		this->velocity.Y = 0;
	}

	// Move the object each frame by the velocity value
	this->Move(this->velocity * _METER * t_delta_time);
}

void Dynamic::Move(const Vector2D t_offset)
{
	// Offset the object by the specified Vector2D
	this->SetPosition(this->GetPosition() + t_offset);
}
