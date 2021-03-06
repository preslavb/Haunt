#pragma once
#include "Character.h"

// An enemy class for characters that hurt the player
class Enemy : public Character
{
private:
	// Constants for use in physics calculations
	// Acceleration limit
	const float MAX_ACCELERATION = 5;
	// How much to accelerate each second
	const float RUN_ACCELERATION = 2;
	// Force of the initial jump
	const float JUMP_FORCE = 60;
	// Force of the jump after hitting an enemy
	const float JUMP_FORCE_HIT = 40;
	// Force to limit to if the button is released (causing the character to stop moving up)
	const float JUMP_LIMIT = 10;

	// If the enemy should start moving
	bool isEnabled = false;

	// Hooks for enemy collisions
	void HookEnemyEvents();
protected:
	double baseSpeed = 5;
public:
	// Constructors taking in a texture, position (optional) ,rotation(optional) and health(optional)
	Enemy(Texture* t_texture_to_use, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, int t_new_health, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));

	// Movement functions hiding the ones in the normal character
	void MoveLeft(float t_delta_time);
	void MoveRight(float t_delta_time);

	// An override of the die function for characters
	void Die() override;

	// Update the enemy character
	void Update(float t_delta_time) override;
};
