#ifndef _DYNAMIC_H
#define _DYNAMIC_H

#include "GameObject.h"

// Any element in the game world that is affected by physics
class Dynamic : public GameObject
{
protected:
	// Whether the object is on the ground
	bool grounded;
public:
	// Constructors taking in a texture, position (optional) and rotation(optional)
	Dynamic(Texture* t_texture_to_use);
	Dynamic(Texture* t_texture_to_use, glm::vec2 t_new_position);
	Dynamic(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation);
	Dynamic(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth);
	~Dynamic();

	// Move the object by offsetting them with a Vector2D value
	virtual void Move(const glm::vec2 t_offset);

	// Update logic for any dynamic objects
	void Update(float t_delta_time) override;
};

#endif // !_DYNAMIC_H
