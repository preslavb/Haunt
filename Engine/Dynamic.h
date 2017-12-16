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
	// Constructors taking in a texture, position (optional), depth(optional), order(optional) and rotation(optional)
	Dynamic(Texture* t_texture_to_use, glm::vec2 t_new_position = glm::vec2(0, 0), float t_new_depth = 1, float t_new_order = 1, float t_new_rotation = 0);
	~Dynamic();

	// Move the object by offsetting them with a Vector2D value
	virtual void Move(const glm::vec2 t_offset);

	// Update logic for any dynamic objects
	void Update(float t_delta_time) override;
};

#endif // !_DYNAMIC_H
