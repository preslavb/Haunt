#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.h"
#include <Engine/KeyState.h>
#include <Engine/InputHandler.h>

// The player's character in the game (receives events from the input manager)
[event_receiver(native)]
class Player : public Character
{
private:
	static Player* instance;

	Collider attackCollider;
	// Hook up the receiver to the events in the input manager
	void HookInputEvent();
	void HookCollisionEvents();
	void WasHitByEnemy(Collider* t_other_collider, Collider* t_collider_hit);
	void HasHitEnemy(Collider* t_enemy_collider, Collider* t_friendly_collider);
	void HandleFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider) override;
	void HandleRoofCollision(Collider* t_other_collider, Collider* t_friendly_collider);
	void EscapeFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider) override;
public:
	// Constructors
	Player(Texture* t_texture_to_use, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Player(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Player(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Player(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth, Rect t_custom_collider_dimensions = Rect(0, 0, 0, 0));
	Collider* GetAttackCollider();
	Collider* GetHitCollider();
	~Player();

	static Player* GetInstance(Texture* t_texture_to_use);
	static Player* GetInstance(Texture* t_texture_to_use, glm::vec2 t_new_position);
	static Player* GetInstance(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions);
	static Player* GetInstance();

	// Update logic for the player, based on the time passed from the last frame
	void Update(float t_delta_time) override;
};

#endif // !_PLAYER_H
