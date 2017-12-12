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
	int floorsCollidingWith = 0;
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
	bool isHit = false;

	void HookCharacterCollisionEvents();
	void WasHitByPlayer(Collider* t_player_collider, Collider* t_collider_hit);
	virtual void HandleFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider);
	virtual void EscapeFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider);
	bool IsHit();
public:
	// Constructors taking in a texture, position (optional) ,rotation(optional) and health(optional)
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

	void Ground(float t_ground_height);
	void Unground();
	void Character::SetPosition(glm::vec2 t_new_position) override;

	// Call this method to damage the character
	void Damage(int t_amount_of_damage);
	virtual void Die();

	Collider* GetMainCollider();

	void Move(const glm::vec2 t_offset) override;
};

#endif
