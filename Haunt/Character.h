#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <Engine/Dynamic.h>
#include <Engine/Collider.h>

// Constants for use in physics calculations
// Acceleration limit
const float MAX_ACCELERATION = 40;
// How much to accelerate each second
const float RUN_ACCELERATION = 10;
// Force of the initial jump
const float JUMP_FORCE = 70;
// Force of the jump after hitting an enemy
const float JUMP_FORCE_HIT = 40;
// Force to limit to if the button is released (causing the character to stop moving up)
const float JUMP_LIMIT = 10;

[event_receiver(native)]
class Character : public Dynamic
{
protected:
	// Base speed when moving deliberately
	double baseSpeed = 10;

	// The number of floors colliding with (used to make sure AI doesn't fall off the world when colliding with a wall, might not be necessary anymore
	int floorsCollidingWith = 0;
	// Character hit points
	int health;

	// Is the character currently trying to move deliberately
	bool isMoving;

	// Flag whether the character has jumped and direction of movement
	bool hasJumped;
	bool isMovingRight;
	bool isMovingLeft;

	// The main collider used for all characters. Can be overwritten if needed
	Collider mainCollider;

	// A vector of colliders belonging to the character
	std::vector<Collider*> colliders;

	// Flag whether the character is currently in the state of being hit (has been hit and hasn't hit a floor/wall)
	bool isHit = false;

	// Hook the main collider collision events with corresponding handlers
	void HookCharacterCollisionEvents();

	// Collision Handlers
	void WasHitByPlayer(Collider* t_player_collider, Collider* t_collider_hit);
	virtual void HandleFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider);
	virtual void EscapeFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider);
public:
	// Constructors taking in a texture, position (optional) ,rotation(optional) and health(optional) (should be reworked for the new system of optionals)
	Character(Texture* t_texture_to_use, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, int t_new_health, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));

	// Destructor
	~Character();

	// Movement Funtions
	void MoveRight(float t_delta_time);
	void MoveLeft(float t_delta_time);
	void StopMoving(float t_delta_time);
	void Jump(float t_delta_time);
	void ForceJump(Collider* t_enemy_collider);
	void LimitJump(float t_delta_time);

	// Update logic for a character object
	void Update(float t_delta_time) override;

	// Ground the character to a specific ground height, stopping them from falling
	void Ground(float t_ground_height);

	// Enable falling on the character
	void Unground();

	// Set the position of the character and move the colliders with it, offset by their calculated offset on instantiation
	void Character::SetPosition(glm::vec2 t_new_position) override;

	// Call this method to damage the character
	void Damage(int t_amount_of_damage);

	// Method for killing the character
	virtual void Die();

	// Returns the main collider
	Collider* GetMainCollider();

	// Moves the character with the given offset (along with all of the colliders)
	void Move(const glm::vec2 t_offset) override;

	// Accessor for isHit
	bool IsHit();
};

#endif
