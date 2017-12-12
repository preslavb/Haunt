#include "Game.h"
#include "Engine/CollisionManager.h"
#include "Enemy.h"
#include "Engine/GarbageDestroyer.h"
#include "GL/glut.h"
#include "Floor.h"

// Singleton Class Structure
Game* Game::instance = nullptr;
static TextureManager* textureManager = TextureManager::GetInstance();
static InputHandler* inputHandler = InputHandler::GetInstance();

Game::Game()
{
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_ESCAPE), &Game::TogglePause);
}

void Game::RemoveUIElement(UIElement* t_ui_element)
{
	for (std::vector<UIElement*>::iterator it = uiElements.begin(); it != uiElements.end(); ++it)
	{
		if ((*it) == t_ui_element)
		{
			it = uiElements.erase(it);
			GarbageDestroyer<UIElement*>::GetInstance()->Destroy(t_ui_element);
			break;
		}
	}
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
	MainCamera.Initialize(_WINDOW_WIDTH, _WINDOW_HEIGHT);

	textureManager->TextureNames = {
		"grass", "enemy", "tree1", "character", "UpArrow", "DownArrow", "LeftArrow", "RightArrow", "theBackground", "theBackground2", "title", "debug"
	};

	textureManager->TexturesToUse = {
		"Images\\tile1.png", "Images\\enemy.png", "Images\\tree1.png", "Images\\character.png", "Images\\UpArrow.png",
		"Images\\DownArrow.png", "Images\\LeftArrow.png", "Images\\RightArrow.png", "Images\\theBackground.png", "Images\\theBackground2.png", "Images\\title.png", "Images\\CollisionDebug.png"
	};

	textureManager->Initialise();

	spriteBatch.Initialize();

	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground"), glm::vec2(-textureManager->GetTexture("theBackground")->GetTextureWidth()/2, -textureManager->GetTexture("theBackground")->GetTextureHeight() / 2)));
	gameObjects.back()->SetDepth(0);
	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground2"), glm::vec2(-textureManager->GetTexture("theBackground2")->GetTextureWidth() / 2, -400)));
	gameObjects.back()->SetDepth(0.05);
	gameObjects.push_back(Player::GetInstance(textureManager->GetTexture("character"), glm::vec2(500, 100), Rect(glm::vec2(textureManager->GetTexture("character")->GetTextureWidth() / 4, 0), glm::vec2(textureManager->GetTexture("character")->GetTextureWidth()/2, textureManager->GetTexture("character")->GetTextureHeight()/2))));
	gameObjects.back()->SetDepth(1, new float(2));
	gameObjects.push_back(new Enemy(textureManager->GetTexture("enemy"), glm::vec2(4000, 100)));
	gameObjects.back()->SetDepth(1, new float(2));
	gameObjects.push_back(new Enemy(textureManager->GetTexture("enemy"), glm::vec2(1500, 100)));
	gameObjects.back()->SetDepth(1, new float(2));
	gameObjects.push_back(new Floor(textureManager->GetTexture("grass"), glm::vec2(0, 0), glm::vec2(5000, 200), Rect(glm::vec2(0, 0), glm::vec2(5000, 100))));
	gameObjects.back()->SetDepth(1);
	gameObjects.push_back(new Floor(textureManager->GetTexture("grass"), glm::vec2(1000, 250), glm::vec2(300, 100), Rect(glm::vec2(1000, 250), glm::vec2(300, 50))));
	gameObjects.back()->SetDepth(1);
	gameObjects.push_back(new Floor(textureManager->GetTexture("grass"), glm::vec2(5000, 0), glm::vec2(5000, 200), Rect(glm::vec2(5000, 0), glm::vec2(5000, 100))));
	gameObjects.back()->SetDepth(1);
	gameObjects.push_back(new Floor(textureManager->GetTexture("grass"), glm::vec2(-100, 0), glm::vec2(100, MainCamera.GetScreenDimensions().y)));
	gameObjects.back()->SetDepth(1);
	gameObjects.push_back(new GameObject(textureManager->GetTexture("tree1"), glm::vec2(200, 10)));
	gameObjects.back()->SetDepth(1);

	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("UpArrow"), glm::vec2(150.0f, 150.0f), glm::vec2(100, 100)));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("DownArrow"), glm::vec2(150.0f, 50.0f), glm::vec2(100, 100)));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("LeftArrow"), glm::vec2(50.0f, 50.0f), glm::vec2(100, 100)));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("RightArrow"), glm::vec2(250.0f, 50.0f), glm::vec2(100, 100)));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("title"), glm::vec2(0.0f, 0.0f), glm::vec2(MainCamera.GetScreenDimensions())));

	for (UIElement* uiElement : uiElements)
	{
		__hook(&UIElement::WasDestroyed, uiElement, &Game::RemoveUIElement);
	}

	worldShaderProgram.CompileShaders("Shaders/worldShader.vert", "Shaders/worldShader.frag");

	worldShaderProgram.AddAttribute("vertexPosition");
	worldShaderProgram.AddAttribute("vertexColor");
	worldShaderProgram.AddAttribute("vertexUV");
	worldShaderProgram.AddAttribute("depth");

	worldShaderProgram.LinkShaders();

	uiShaderProgram.CompileShaders("Shaders/UIShader.vert", "Shaders/UIShader.frag");
	uiShaderProgram.AddAttribute("vertexPosition");
	uiShaderProgram.AddAttribute("vertexColor");
	uiShaderProgram.AddAttribute("vertexUV");

	uiShaderProgram.LinkShaders();

	textShaderProgram.CompileShaders("Shaders/textShader.vert", "Shaders/textShader.frag");
	textShaderProgram.AddAttribute("vertexPosition");
	textShaderProgram.AddAttribute("vertexColor");
	textShaderProgram.AddAttribute("vertexUV");

	textShaderProgram.LinkShaders();

	lastTime = SDL_GetTicks();
}

void Game::Run(SDL_Window* t_window)
{
	bool loop = true;

	while (loop)
	{
		float elapsedTime = 0;

		//We get the time that passed since the last frame
		if (!paused)
		{
			elapsedTime = this->GetElapsedSeconds();
		}
		else
		{
			this->GetElapsedSeconds();
		}
		

		loop = inputHandler->Update(loop, elapsedTime);
		this->Update();
		this->Update(elapsedTime);
		this->Render(t_window);
	}
}

void Game::TogglePause(float t_delta_time)
{
	paused = !paused;
}

void Game::Render(SDL_Window* t_window) const
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	instance->worldShaderProgram.Use();

	GLint cameraLocation = Game::GetInstance()->worldShaderProgram.GetUniformLocation("projectionMatrix");
	glm::mat4 cameraMatrix = MainCamera.GetCameraMatrix();
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	instance->spriteBatch.Begin(QuadSortType::FRONT_TO_BACK);

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	Color tint;

	if (!paused)
	{
		tint.R = 255;
		tint.G = 255;
		tint.B = 255;
		tint.A = 255;
	}
	else
	{
		tint.R = 200;
		tint.G = 200;
		tint.B = 200;
		tint.A = 255;
	}
	

	for (GameObject* const gameObject : gameObjects)
	{
		instance->spriteBatch.Draw(gameObject, tint);
	}

	/*for (Collider* collisionManager : *CollisionManager::GetInstance()->GetVectorOfColliders())
	{
		instance->spriteBatch.Draw(collisionManager, TextureManager::GetInstance()->GetTexture("debug"), tint);
	}*/

	instance->spriteBatch.End();

	instance->spriteBatch.RenderBatches();

	instance->uiShaderProgram.Use();

	GLint cameraTransformation = Game::GetInstance()->uiShaderProgram.GetUniformLocation("projectionMatrix");
	glm::mat4 orthographicMatrix = MainCamera.GetOrthoMatrix();
	glUniformMatrix4fv(cameraTransformation, 1, GL_FALSE, &(orthographicMatrix[0][0]));

	instance->spriteBatch.Begin(QuadSortType::TEXTURE);

	for (UIElement* const element : uiElements)
	{
		instance->spriteBatch.Draw(element, element->GetTint());
	}
	
	instance->spriteBatch.End();

	instance->spriteBatch.RenderBatches();

	TextureManager::GetInstance()->WriteText("Score: " + to_string(score), glm::vec2(-MainCamera.GetScreenDimensions().x + 10, MainCamera.GetScreenDimensions().y - 100));

	SDL_GL_SwapWindow(t_window);
}

void Game::Render()
{
}

void Game::AddScore()
{
	score += 100;
}

// Updates detatched from timing (frame based)
void Game::Update()
{
	CoroutineManager<bool>::Update();
	CollisionManager::GetInstance()->Update();
}

void Game::Update(float t_delta_time)
{
	InputHandler::GetInstance()->Update(true, t_delta_time);

	for (vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update();
		(*it)->Update(t_delta_time);
	}

	MainCamera.Update();

	this->frames++;
	this->runTime += t_delta_time;
	this->framerate = frames / runTime;

	if(runTime > 1)
	{
		runTime -= 1;
		frames = 1;
	}

	GarbageDestroyer<Character*>::GetInstance()->ClearGarbage();
	GarbageDestroyer<UIElement*>::GetInstance()->ClearGarbage();
}

void Game::DisplayEndScreen()
{
	
}

float Game::GetElapsedSeconds()
{
	const float currentTime = gameStarted ? SDL_GetTicks() : gameStarted = true;

	const float seconds = (currentTime - lastTime) / (60 * 10);
	this->lastTime = currentTime;
	
	// If the current frame took more than a fifth of a second to update, that means there was probably a lag spike, so the counter should be restarted (prevents too much happening without the player seeing)
	return fmod(seconds, 0.2);
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

std::vector<GameObject*>* Game::GetGameObjects()
{
	return &gameObjects;
}

std::vector<UIElement*>* Game::GetUIElements()
{
	return &uiElements;
}
