#ifndef _GAME_H
#define _GAME_H

#include "Player.h"
#include <Engine/GameObject.h>
#include <Engine/TextureManager.h>
#include <Engine/Camera2D.h>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLProgram.h>
#include <Engine/UIElement.h>
#include <Engine/InputHandler.h>

using namespace std;

// The Game object, responsible for running the game loop and calling any render functions, update functions and initialisations
[event_receiver(native)]
class Game
{
public:
	// The main camera
	Camera2D MainCamera;

	// Constructor
	Game();
	void RemoveUIElement(UIElement* t_ui_element);

	// Initialise logic, container for any other classes' initialisations
	void Initialise(SDL_Window* t_window);

	// Reset the game state (not currently in working condition)
	void Reset(float t_delta_time);

	// The main game loop
	void Run(SDL_Window* t_window);

	// Toggle the pause state of the game
	void TogglePause(float t_delta_time);

	// Clean up before closing the window and the game
	static void CleanUp(SDL_Window* t_window);

	// Accessors for the active game objects and ui elements in the game
	std::vector<GameObject*>* GetGameObjects();
	std::vector<UIElement*>* GetUIElements();

	// Render logic for displaying items on the screen
	void Render(SDL_Window* t_window) const;
	static void Render();

	// Functions to add score
	void AddScore();
	void AddScore(int t_score);

	// Update loop for any model updates before render
	static void Update();
	// Update loop with a tracker of passed time since last frame (needed for physics)
	void Update(float t_delta_time);

	// End game event handler (can be called outside of an event with double nulls as well)
	void EndGame(Collider* t_first_collider, Collider* t_second_collider);

	// Get the seconds elapsed since last frame
	float GetElapsedSeconds();

	// Get the singleton instance
	static Game* GetInstance();

private:
	// The singleton instance of the game
	static Game* instance;
	
	// The sprite batch to use when rendering
	SpriteBatch spriteBatch;

	// The pause state of the game
	bool paused = false;

	// The shader program for drawing objects in world space
	GLSLProgram worldShaderProgram;

	// The shader program for drawing ui elements in screen space
	GLSLProgram uiShaderProgram;

	// The shader program used for drawing text (not currently used)
	GLSLProgram textShaderProgram;

	// The time recorded last frame
	float lastTime;
	// The total run time
	float runTime;

	// The current framerate (inaccurate)
	float framerate;

	// The number of frames drawn
	int frames;

	// The current score
	int score = 0;

	// The game state flags
	bool gameStarted = false;
	bool gameEnded = false;

	// A vector of Game Objects and UI elements in the game
	//TODO: (should be moved to a Level class)
	vector<GameObject*> gameObjects;
	vector<UIElement*> uiElements;
};

#endif
