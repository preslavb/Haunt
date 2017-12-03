#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <Engine/Dynamic.h>
#include <Engine/Collider.h>

// Constants for use in physics calculations
// Acceleration limit
const float MAX_ACCELERATION = 30;
// How much to accelerate each second
const float RUN_ACCELERATION = 30;
// Force of the initial jump
const float JUMP_FORCE = 60;
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

	// Character hit points
	int health;

	// Is the character currently trying to move deliberately
	bool isMoving;

	// Flag whether the character has jumped
	bool hasJumped;
	bool isMovingRight;
	bool isMovingLeft;

	Collider mainCollider;

	std::vector<Collider*> colliders;

	void HookCharacterCollisionEvents();
	void TestCollisionsCharacter();
	void WasHitByPlayer();
public:
	// Constructors taking in a texture, position (optional) ,rotation(optional) and health(optional)
	Character(Texture* t_texture_to_use);
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position);
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation);
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth);
	Character(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, int t_new_health);

	// Destructor
	~Character();

	// Movement Funtions
	void MoveRight(float t_delta_time);
	void MoveLeft(float t_delta_time);
	void StopMoving(float t_delta_time);
	void Jump(float t_delta_time);
	void ForceJump();
	void LimitJump(float t_delta_time);

	// Update logic for a character object
	void Update(float t_delta_time) override;

	// Call this method to damage the character
	void Damage(int t_amount_of_damage);
	void Die();

	void Move(const glm::vec2 t_offset) override;
};

#endif
