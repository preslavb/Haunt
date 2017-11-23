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
void Game::Initialise(SDL_Window* t_window)
{
	lastTime = 0;
	textureManager->Initialise();

	Vector2D newVector;

	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground"), Vector2D(624, 410)));
	gameObjects.push_back(new Player(textureManager->GetTexture("grass"), Vector2D(500, 500)));

	colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");

	colorProgram.AddAttribute("vertexPosition");
	colorProgram.AddAttribute("vertexColor");
	colorProgram.AddAttribute("vertexUV");

	colorProgram.LinkShaders();
}

void Game::Run(SDL_Window* t_window)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		const float elapsedTime = this->GetElapsedSeconds();

		loop = inputHandler->Update(loop);
		this->Update();
		this->Update(elapsedTime);
		this->Render(t_window);
	}
}

void Game::Render(SDL_Window* t_window) const
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->Render();
	}

	Game::GetInstance()->colorProgram.Use();

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, *TextureManager::GetInstance()->GetTexture("theBackground"));
	GLint textureLocation = Game::GetInstance()->colorProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	Sprite testSprite;
	testSprite.Initialize(-1, 0, 1, 1);
	testSprite.Render();

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_GL_SwapWindow(t_window);
}

void Game::Render()
{
}

// Updates detatched from timing (frame based)
void Game::Update()
{
	CoroutineManager<bool>::Update();
	InputHandler::GetInstance()->Update(true);
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
