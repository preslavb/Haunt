#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>

// Includes used throughout the whole game
#include "GameIncludes.h"

using namespace std;

class Game
{
public:
	Game();

	void initialise(SDL_Window* window, SDL_Renderer* renderer);
	void run(SDL_Window* window, SDL_Renderer* renderer);
	void cleanUp(SDL_Window* window);
	void render(SDL_Window* window, SDL_Renderer* renderer);
	void render(SDL_Window* window, SDL_Renderer* renderer, double rotationAngle, SDL_Point* spriteCentre);
	void update();
	void update(float deltaTime);
	bool getInput(bool loop);
	float getElapsedSeconds();

	static Game* getInstance();

private:

	static Game* instance;

	// game related variables
	float lastTime;
};

#endif
