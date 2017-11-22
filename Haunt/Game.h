#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>

// Includes used throughout the whole game
#include "GameIncludes.h"
#include "GameObject.h"

using namespace std;

// The Game object, responsible for running the game loop and calling any render functions, update functions and initialisations
class Game
{
public:
	// Constructor
	Game();

	// Initialise logic, container for any other classes' initialisations
	void Initialise(SDL_Window* t_window, SDL_Renderer* t_renderer);

	// The main game loop
	void Run(SDL_Window* t_window, SDL_Renderer* t_renderer);

	// Clean up before closing the window and the game
	static void CleanUp(SDL_Window* t_window);

	// Render logic for displaying items on the screen
	void Render(SDL_Window* t_window, SDL_Renderer* t_renderer) const;
	static void Render(SDL_Renderer* t_renderer);

	// Update loop for any model updates before render
	static void Update();
	// Update loop with a tracker of passed time since last frame (needed for physics)
	void Update(float t_delta_time);

	// Get the seconds elapsed since last frame
	float GetElapsedSeconds();

	// Get the singleton instance
	static Game* GetInstance();

private:
	// The singleton instance of the game
	static Game* instance;

	// The time recorded last frame
	float lastTime;
	float runTime;

	float framerate;
	int frames;

	// A vector of Game Objects in the game
	//TODO: (should be moved to a Level class)
	vector<GameObject*> gameObjects;
};

#endif
