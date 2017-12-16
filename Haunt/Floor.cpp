#include "Floor.h"

Floor::Floor(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions) : GameObject(t_texture_to_use, t_new_position), floorCollider(t_new_position, Rect(glm::vec2(0, 0), glm::vec2(500, 500)), this)
{
	type = "Floor";
	HookCollisionEvents();
}

Floor::Floor(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_dimensions, Rect t_custom_collider_dimensions) : GameObject(t_texture_to_use, t_new_position), floorCollider(t_custom_collider_dimensions.IsValid() ? glm::vec2(t_custom_collider_dimensions.GetPosition()) : t_new_position, t_custom_collider_dimensions.IsValid()? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), t_new_dimensions), this)
{
	type = "Floor";

	// If custom dimensions are provided for the collider, use them, and set the collision distance based on them
	dimensions = (t_new_dimensions);
	floorCollider.SetCollisionDistance(sqrt(pow(dimensions.x, 2) + pow(dimensions.y, 2)));

	HookCollisionEvents();
}

Floor::~Floor()
{
}

//----------------Obsolete------------//
void Floor::HookCollisionEvents()
{
}

void Floor::HandleCollision(Collider* t_other_collider)
{
}

void Floor::HandleEscape(Collider* t_other_collider)
{
}
