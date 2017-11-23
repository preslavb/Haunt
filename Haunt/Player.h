#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.h"

// The player's character in the game (receives events from the input manager)
[event_receiver(native)]
class Player : public Character
{
private:
	// Hook up the receiver to the events in the input manager
	void HookInputEvent();
public:
	// Constructors
	Player(GLuint* t_texture_to_use);
	Player(GLuint* t_texture_to_use, Vector2D t_new_position);
	Player(GLuint* t_texture_to_use, Vector2D t_new_position, float t_new_rotation);
	~Player();

	// Update logic for the player, based on the time passed from the last frame
	void Update(float t_delta_time) override;
};

#endif // !_PLAYER_H
