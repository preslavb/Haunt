#ifndef _GAME_H
#define _GAME_H

#include "Player.h"
#include <Engine/GameObject.h>
#include <Engine/TextureManager.h>
#include <Engine/Camera2D.h>
#include <Engine/SpriteBatch.h>
#include "Engine/GLSLProgram.h"

using namespace std;

// The Game object, responsible for running the game loop and calling any render functions, update functions and initialisations
class Game
{
public:
	// The main camera
	Camera2D MainCamera;

	// Constructor
	Game();

	// Initialise logic, container for any other classes' initialisations
	void Initialise(SDL_Window* t_window);

	// The main game loop
	void Run(SDL_Window* t_window);

	// Clean up before closing the window and the game
	static void CleanUp(SDL_Window* t_window);

	// Render logic for displaying items on the screen
	void Render(SDL_Window* t_window) const;
	static void Render();

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
	
	SpriteBatch spriteBatch;

	GLSLProgram colorProgram;

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
