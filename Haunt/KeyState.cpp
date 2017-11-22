#include "KeyState.h"

KeyState::KeyState(const Uint16 t_key_of)
{
	StateKey = t_key_of;
}


KeyState::~KeyState()
{
}

void KeyState::SetCurrentState(Uint32 t_sdl_state)
{
	switch(t_sdl_state)
	{
	case SDL_KEYDOWN:
		if (CurrentState != Held)
		{
			CurrentState = Pressed;
			__raise this->OnKeyPressed();
			CoroutineManager<bool>::StartCoroutine(KeyHeldCoroutine(this));
		}
		else
		{
			CurrentState = Held;
		}
		break;
	case SDL_KEYUP:
		CurrentState = Released;
		__raise this->OnKeyReleased();
		CurrentState = None;
		break;
	default:
		CurrentState = None;
		break;
	}
}

Coroutine<bool> KeyState::KeyHeldCoroutine(KeyState* t_key_state)
{
	co_yield true;
	
	t_key_state->CurrentState = KeyState::Held;

	while (t_key_state->CurrentState == KeyState::Held)
	{
		__raise t_key_state->WhenKeyHeld();
		co_yield true;
	}
	
	co_return false;
}