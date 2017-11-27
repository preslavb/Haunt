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
	// Hook up the receiver to the events in the input manager
	void HookInputEvent();
public:
	// Constructors
	Player(Texture* t_texture_to_use);
	Player(Texture* t_texture_to_use, glm::vec2 t_new_position);
	Player(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation);
	~Player();

	static Player* GetInstance();

	// Update logic for the player, based on the time passed from the last frame
	void Update(float t_delta_time) override;
};

#endif // !_PLAYER_H
