#include "Game.h"

#include "Player.h"

// Singleton Class Structure
Game* Game::instance = nullptr;
static TextureManager* textureManager = TextureManager::GetInstance();
static InputHandler* inputHandler = InputHandler::GetInstance();

Game::Game()
{
}

Game* Game::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Game();
	}
	return instance;
}

// Initialise all game variables and renderer before the game loop starts
void Game::Initialise(SDL_Window* t_window, SDL_Renderer* t_renderer)
{
	lastTime = 0;

	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(t_renderer, 255, 0, 0, 255);
	SDL_RenderPresent(t_renderer);

	textureManager->SetRenderer(t_renderer);
	textureManager->Initialise();

	Vector2D newVector;

	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground"), Vector2D(624, 410)));
	gameObjects.push_back(new Player(textureManager->GetTexture("grass"), Vector2D(500, 500)));
}

void Game::Run(SDL_Window* t_window, SDL_Renderer* t_renderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		const float elapsedTime = this->GetElapsedSeconds();

		loop = inputHandler->Update(loop);
		this->Update();
		this->Update(elapsedTime);
		this->Render(t_window, t_renderer);
	}
}

void Game::Render(SDL_Window* t_window, SDL_Renderer* t_renderer) const
{
	SDL_RenderClear(t_renderer);

	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->Render(t_renderer);
	}

	SDL_RenderPresent(t_renderer);
}

void Game::Render(SDL_Renderer* t_renderer)
{
	SDL_RenderPresent(t_renderer);
}

// Updates detatched from timing (frame based)
void Game::Update()
{
	CoroutineManager<bool>::Update();
	cout << "Frame: ";
}

void Game::Update(float t_delta_time)
{
	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->Update();
		gameObject->Update(t_delta_time);
	}
	this->frames++;
	this->runTime += t_delta_time;
	this->framerate = frames / runTime;

	if(runTime > 1)
	{
		runTime -= 1;
		frames = 1;
	}
}


float Game::GetElapsedSeconds()
{
	const float currentTime = SDL_GetTicks();
	const float seconds = (currentTime - lastTime) / (60 * 10);
	this->lastTime = currentTime;
	
	return seconds;
}

void Game::CleanUp(SDL_Window* t_window)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(t_window);

	// Destroy the window
	SDL_DestroyWindow(t_window);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}
