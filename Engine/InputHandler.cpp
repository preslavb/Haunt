#include "KeyState.h"
#include "InputHandler.h"
#include <experimental/resumable>

// Set the initial instance of the Input Handler singleton
InputHandler* InputHandler::instance = nullptr;

// Constructor, initialising all of the registered keys to the controlStates map
InputHandler::InputHandler()
{
	controlStates.begin();
	for (const Uint8 control : REGISTERED_CONTROLS)
	{
		controlStates.insert(pair<const Uint8, KeyState>(control, KeyState(control)));
	}
}

// Destructor
InputHandler::~InputHandler()
{
}

// Return the singleton instance of the Input Handler
InputHandler* InputHandler::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputHandler();
	}
	return instance;
}

// Get the current key state of the Key
KeyState::KeyStates InputHandler::GetKeyState(const Uint8 t_sdl_key)
{
	return GetInstance()->controlStates.find(t_sdl_key)->second.CurrentState;
}

// Get the current key state class pointer of the Key
KeyState* InputHandler::GetKeyStateClass(const Uint8 t_sdl_key)
{
	return &GetInstance()->controlStates.find(t_sdl_key)->second;
}

// Update the logic of the Input Handler (most of the logic should be contained within events triggered by SetCurrentState)
bool InputHandler::Update(bool t_loop, float t_delta_time)
{
	SDL_Event event;
		
	// Poll the current key events
	while (SDL_PollEvent(&event))
	{
		// If the quit button or the escape button are pressed, stop the update loop
		if (event.type == SDL_QUIT)
		{
			t_loop = false;
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			
		}

		// Add the pressed or released key to the controlStates storage
		if (event.type == SDL_MOUSEBUTTONDOWN ||
			event.type == SDL_MOUSEBUTTONUP ||
			event.type == SDL_KEYDOWN ||
			event.type == SDL_KEYUP)
		{
			GetInstance()->controlStates.find(event.key.keysym.sym) != GetInstance()->controlStates.end() ? GetInstance()->controlStates.find(event.key.keysym.sym)->second.SetCurrentState(event.type, t_delta_time) : nullptr;
		}
	}

	return t_loop;
}
