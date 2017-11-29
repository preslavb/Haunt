#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include "KeyState.h"
#include "SDL/SDL.h"
#include <unordered_map>

// The controls that the game could ever care about
static const Uint8 REGISTERED_CONTROLS[] = { SDLK_UP, SDLK_LEFT, SDLK_RIGHT, SDLK_DOWN };

// A singleton input handler
class InputHandler
{
private:
	// The private input handler instance
	static InputHandler* instance;
	
	// The states of any keys registered in the game (any other keys just get thrown)
	unordered_map<Uint8, KeyState> controlStates;
public:
	// Constructor and destructor
	InputHandler();
	~InputHandler();

	// Get the instance of the singleton
	static InputHandler* GetInstance();

	// Get the key state of an SDLK_KEY
	static KeyState::KeyStates GetKeyState(Uint8 t_sdl_key);
	static KeyState* GetKeyStateClass(Uint8 t_sdl_key);

	// Update the Handler
	static bool Update(bool t_loop);
};

#endif // !_INPUTHANDLER_H
