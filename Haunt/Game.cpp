#include "Game.h"

// Singleton Class Structure
Game* Game::instance = NULL;
static TextureManager* textureManager = TextureManager::getInstance();

Game::Game()
{

}

Game* Game::getInstance()
{
	if (instance == NULL)
	{
		instance = new Game();
	}
	return Game::instance;
}

// Initialise all game variables and renderer before the game loop starts
void Game::initialise(SDL_Window* window, SDL_Renderer* renderer)
{
	lastTime = 0;
	
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
	
	textureManager->setRenderer(renderer);
	textureManager->initialise();
}

void Game::run(SDL_Window* window, SDL_Renderer* renderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		float elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(window, renderer);
	}
}

void Game::render(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::render(SDL_Window* window, SDL_Renderer* renderer, double rotationAngle, SDL_Point* spriteCentre)
{
	
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	
}

void Game::update(float deltaTime)
{

}

bool Game::getInput(bool loop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			loop = false;
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					loop = false;
					break;
				default:
					break;
				}

			default:
				break;
		}

	}
	return loop;
}

float Game::getElapsedSeconds()
{
	float currentTime = SDL_GetTicks() ;
	float seconds = (currentTime - lastTime)/(60*1000);
	this->lastTime = currentTime;
	return seconds;
}

void Game::cleanUp(SDL_Window* window)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(window);

	// Destroy the window
	SDL_DestroyWindow(window);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

