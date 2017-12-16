#include "KeyState.h"

// Constructor
KeyState::KeyState(const Uint16 t_key_of)
{
	// Set the key associated with this KeyState object
	StateKey = t_key_of;
}

//Destructor
KeyState::~KeyState()
{
}

void KeyState::SetCurrentState(Uint32 t_sdl_state, float t_delta_time)
{
	switch(t_sdl_state)
	{
	// If the key was pressed and was not held, raise any functions that have subscribed to this key press, then start the coroutine for running code when the key is held
	case SDL_KEYDOWN:
		if (CurrentState != Held)
		{
			CurrentState = Pressed;
			__raise this->OnKeyPressed(t_delta_time);
			CoroutineManager<bool>::StartCoroutine(KeyHeldCoroutine(this, t_delta_time));
		}
		else
		{
			// The input event has fired again, but the key state is already held, so continue the held state
			CurrentState = Held;
		}
		break;
	// Run any functions that have subscribed to this key release, then set the state to none (not pressed, held or just released)
	case SDL_KEYUP:
		CurrentState = Released;
		__raise this->OnKeyReleased(t_delta_time);
		CurrentState = None;
		break;
	default:
		CurrentState = None;
		break;
	}
}

Coroutine<bool> KeyState::KeyHeldCoroutine(KeyState* t_key_state, float t_delta_time)
{
	// Wait for a frame before running the held coroutine (this makes sure that holding only happens one frame after pressing, and makes it possible for a press and release without holding)
	co_yield true;
	
	// If the key was not released immediately after being pressed, set the key state to held
	if (t_key_state->CurrentState != None) t_key_state->CurrentState = KeyState::Held;

	// While the key state stays Held, run any functions that are subscribed to the key held event once each frame
	while (t_key_state->CurrentState == KeyState::Held)
	{
		__raise t_key_state->WhenKeyHeld(t_delta_time);
		co_yield true;
	}
	
	// Exit out of the coroutine once the key is no longer being held
	co_return false;
}