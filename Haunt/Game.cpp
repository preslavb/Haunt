#include "Game.h"

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
	spriteBatch.Initialize();

	glm::vec2 newVector;

	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground"), glm::vec2(0, 0)));
	gameObjects.push_back(new Player(textureManager->GetTexture("grass"), glm::vec2(500, 500)));

	colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");

	colorProgram.AddAttribute("vertexPosition");
	colorProgram.AddAttribute("vertexColor");
	colorProgram.AddAttribute("vertexUV");

	colorProgram.LinkShaders();

	camera.Initialize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
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

	instance->colorProgram.Use();

	GLint cameraLocation = Game::GetInstance()->colorProgram.GetUniformLocation("projectionMatrix");
	glm::mat4 cameraMatrix = camera.GetCameraMatrix();
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	instance->spriteBatch.Begin();

	glm::vec4 position(0.0f, 0.0f, 700.0f, 500.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	GLuint* texture = TextureManager::GetInstance()->GetTexture("theBackground")->GetTextureID();
	Color tint;
	tint.R = 255;
	tint.G = 255;
	tint.B = 255;
	tint.A = 255;

	instance->spriteBatch.Draw(position, uv, *texture, 0, tint);

	instance->spriteBatch.End();

	instance->spriteBatch.RenderABatch();

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
	camera.Update();

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
