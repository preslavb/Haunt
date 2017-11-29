#pragma once

#include "GameConstants.h"
#include "CoroutineManager.h"

[event_source(native)]
// Container class for storing the state of a key and the source for input event listeners
class KeyState
{
public:
	// Constructor taking an SDLK_KEY value to bind to this Key State
	KeyState(Uint16 t_key_of);

	// Destructor
	~KeyState();

	// The different states that a key can have
	enum KeyStates
	{
		Pressed,
		Held,
		Released,
		None
	};

	// The key the object is linked to
	Uint16 StateKey;

	// The state of the key last frame
	KeyStates PreviousState = None;

	// The state of the key this frame
	KeyStates CurrentState = None;

	// Set the state of the key using an SDL_KEYSTATE (SDL_KEYDOWN, SDL_KEYUP)
	void SetCurrentState(Uint32 t_sdl_state);

	// The coroutine to run for a held key
	Coroutine<bool> KeyHeldCoroutine(KeyState* t_key_state);

	// Events to fire for the different states
	__event void OnKeyPressed();
	__event void OnKeyReleased();
	__event void WhenKeyHeld();
};

