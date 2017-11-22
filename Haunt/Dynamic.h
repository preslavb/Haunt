#ifndef _DYNAMIC_H
#define _DYNAMIC_H

#include "GameObject.h"

// Any element in the game world that is affected by physics
class Dynamic : public GameObject
{
protected:
	// Acceleration applied to velocity and incremented each frame
	Vector2D acceleration;

	// Current velocity of the object
	Vector2D velocity;

	// Whether the object is on the ground
	bool grounded;
public:
	// Constructors taking in a texture, position (optional) and rotation(optional)
	Dynamic(Texture* t_texture_to_use);
	Dynamic(Texture* t_texture_to_use, Vector2D t_new_position);
	Dynamic(Texture* t_texture_to_use, Vector2D t_new_position, float t_new_rotation);
	~Dynamic();

	// Accessors to velocity and acceleration
	Vector2D GetVelocity() const;
	Vector2D GetAcceleration() const;
	void SetVelocity(Vector2D t_new_velocity);
	void SetAcceleration(Vector2D t_new_acceleration);

	// Move the object by offsetting them with a Vector2D value
	void Move(const Vector2D t_offset);

	// Update logic for any dynamic objects
	void Update(float t_delta_time) override;
};

#endif // !_DYNAMIC_H
