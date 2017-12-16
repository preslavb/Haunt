#include "Game.h"
#include "Engine/CollisionManager.h"
#include "Enemy.h"
#include "GL/glut.h"
#include "Floor.h"
#include "Engine/GarbageDestroyer.h"
#include "Engine/SoundsManager.h"
#include <fstream>

// Singleton Class Structure
Game* Game::instance = nullptr;

// Initialize the texture an input managers
static TextureManager* textureManager = TextureManager::GetInstance();
static InputHandler* inputHandler = InputHandler::GetInstance();

Game::Game()
{
	// Hook up the pause input
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_ESCAPE), &Game::TogglePause);
}

void Game::RemoveUIElement(UIElement* t_ui_element)
{
	// Go through all of the elements, looking for the one specified
	for (std::vector<UIElement*>::iterator it = uiElements.begin(); it != uiElements.end(); ++it)
	{
		// If the iterator value fits the passed element, erase the given element and break out of the function
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
	// If an instance of the game does not exist yet, create it
	if (instance == nullptr)
	{
		instance = new Game();
	}

	// Return the instance of the game
	return instance;
}

// Initialise all game variables and renderer before the game loop starts
void Game::Initialise(SDL_Window* t_window)
{
	// Initialize the main camera
	MainCamera.Initialize(_WINDOW_WIDTH, _WINDOW_HEIGHT);

	//---------------- Set up the textures needed to load ----------//
	textureManager->TextureNames = {
		"title", "grass", "enemy", "tree1", "character", "UpArrow", "DownArrow", "LeftArrow", "RightArrow", "theBackground", "theBackground2", "debug"
	};

	textureManager->TexturesToUse = {
		"./Images/title.png", "./Images/tile1.png", "./Images/enemy.png", "./Images/tree1.png", "./Images/character.png", "./Images/UpArrow.png",
		"./Images/DownArrow.png", "./Images/LeftArrow.png", "./Images/RightArrow.png", "./Images/theBackground.png", "./Images/theBackground2.png", "./Images/CollisionDebug.png"
	};
	//---------------- Set up the textures needed to load ----------//

	// Initialize the texture manager with the above values
	textureManager->Initialise();

	// Initialize the sprite batch used for rendering
	spriteBatch.Initialize();

	//---------------- Set up the sounds needed to load ----------//
	SoundsManager::GetInstance()->SoundEffectNames = {
		"Jump", "Squash", "Whoosh"
	};

	SoundsManager::GetInstance()->SoundEffectFiles = {
		"SoundFX/Jump.wav", "SoundFX/Squash.wav", "SoundFX/Whoosh.wav"
	};
	//---------------- Set up the textures needed to load ----------//

	// Initialize the sounds manager with the above values
	SoundsManager::GetInstance()->Initialize();

	//---------------- Populate the game world with different kinds of game objects ----------//
	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground"), glm::vec2(-textureManager->GetTexture("theBackground")->GetTextureWidth()/2, -textureManager->GetTexture("theBackground")->GetTextureHeight() / 2)));
	gameObjects.back()->SetDepth(0);
	gameObjects.push_back(new GameObject(textureManager->GetTexture("theBackground2"), glm::vec2((-textureManager->GetTexture("theBackground2")->GetTextureWidth() / 2) + 100, -400)));
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
	gameObjects.push_back(new Floor(textureManager->GetTexture("grass"), glm::vec2(10000, 0), glm::vec2(100, MainCamera.GetScreenDimensions().y)));
	gameObjects.back()->SetDepth(1);
	gameObjects.back()->SetType("EndGame");
	gameObjects.push_back(new GameObject(textureManager->GetTexture("tree1"), glm::vec2(200, 10)));
	gameObjects.back()->SetDepth(1);
	gameObjects.push_back(new GameObject(textureManager->GetTexture("tree1"), glm::vec2(6000, 10)));
	gameObjects.back()->SetDepth(1.3, new float(3));
	//---------------- Populate the game world with different kinds of game objects ----------//

	//---------------- Initialize the intro screen UI Elements ----------//
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("title"), glm::vec2(0.0f, 0.0f), glm::vec2(MainCamera.GetScreenDimensions()), true));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("UpArrow"), glm::vec2(150.0f, 150.0f), glm::vec2(100, 100), true));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("DownArrow"), glm::vec2(150.0f, 50.0f), glm::vec2(100, 100), true));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("LeftArrow"), glm::vec2(50.0f, 50.0f), glm::vec2(100, 100), true));
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("RightArrow"), glm::vec2(250.0f, 50.0f), glm::vec2(100, 100), true));

	// Hook up the fade out destroy event with the remove UI elements function
	for (UIElement* uiElement : uiElements)
	{
		__hook(&UIElement::WasDestroyed, uiElement, &Game::RemoveUIElement);
	}
	//---------------- Initialize the intro screen UI Elements ----------//

	// Compile the shaders into the world shader program
	worldShaderProgram.CompileShaders("Shaders/worldShader.vert", "Shaders/worldShader.frag");

	// Set up the shader attributes
	worldShaderProgram.AddAttribute("vertexPosition");
	worldShaderProgram.AddAttribute("vertexColor");
	worldShaderProgram.AddAttribute("vertexUV");
	worldShaderProgram.AddAttribute("depth");

	// Link the vert and frag shaders into the world shader program
	worldShaderProgram.LinkShaders();

	// Compile the shaders into the UI shader program
	uiShaderProgram.CompileShaders("Shaders/UIShader.vert", "Shaders/UIShader.frag");

	// Set up the shader attributes
	uiShaderProgram.AddAttribute("vertexPosition");
	uiShaderProgram.AddAttribute("vertexColor");
	uiShaderProgram.AddAttribute("vertexUV");

	// Link the vert and frag shaders into the UI shader program
	uiShaderProgram.LinkShaders();

	// Compile the shaders into the text shader program
	textShaderProgram.CompileShaders("Shaders/textShader.vert", "Shaders/textShader.frag");

	// Set up the shader attributes
	textShaderProgram.AddAttribute("vertexPosition");
	textShaderProgram.AddAttribute("vertexColor");
	textShaderProgram.AddAttribute("vertexUV");

	// Link the vert and frag shaders into the text shader program
	textShaderProgram.LinkShaders();

	// Hook up the reset key (not to be used for now, as reset doesn't work correctly)
	//__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_r), &Game::Reset);

	// Start counting time after the initialization of the game finishes
	lastTime = SDL_GetTicks();
}

void Game::Reset(float t_delta_time)
{
	//MainCamera = Camera2D();
	gameObjects.clear();
	uiElements.clear();

	Initialise(nullptr);
}

void Game::Run(SDL_Window* t_window)
{
	// Set the initial value of the game loop to true
	bool loop = true;

	// While the game is running:
	while (loop)
	{
		// Reinitialize the delta time variable
		float elapsedTime = 0;

		// Feed the time that passed since the last frame into it if the game isn't paused
		if (!paused)
		{
			elapsedTime = this->GetElapsedSeconds();
		}

		// Otherwise, just count the time without updating any delta_time related actions
		else
		{
			this->GetElapsedSeconds();
		}
		
		// Update the input handler and check if the game was exited this frame
		loop = inputHandler->Update(loop, elapsedTime);

		// Update the frame and any game logic
		this->Update();
		this->Update(elapsedTime);

		// Render the game
		this->Render(t_window);
	}
}

void Game::TogglePause(float t_delta_time)
{
	// If the game is paused, unpause and vice versa
	paused = !paused;
}

void Game::Render(SDL_Window* t_window) const
{
	// Reset the screen
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start using the world shader program
	instance->worldShaderProgram.Use();

	// Get the projection matrix for the transformation in rendering
	GLint cameraLocation = Game::GetInstance()->worldShaderProgram.GetUniformLocation("projectionMatrix");
	glm::mat4 cameraMatrix = MainCamera.GetCameraMatrix();

	// Feed the projection matrix to the location of the uniform in the shader program
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	// Begin the spritebatch drawing procedure from front to back
	instance->spriteBatch.Begin(QuadSortType::FRONT_TO_BACK);

	// Set the default uvs and the tint
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	Color tint;

	// If the game is unpaused, draw as normal
	if (!paused)
	{
		tint.R = 255;
		tint.G = 255;
		tint.B = 255;
		tint.A = 255;
	}

	// Otherwise, darken the colors so that the player knows what just happened
	else
	{
		tint.R = 200;
		tint.G = 200;
		tint.B = 200;
		tint.A = 255;
	}

	// If the player is hit, turn the whole screen red to signal to the player
	if (Player::GetInstance()->IsHit())
	{
		tint.R = 255;
		tint.G = 50;
		tint.B = 50;
		tint.A = 255;
	}
	
	// Draw the game objects on screen
	for (GameObject* const gameObject : gameObjects)
	{
		instance->spriteBatch.Draw(gameObject, tint);
	}

	// Debug for drawing the colliders on screen if needed
	/*for (Collider* collisionManager : *CollisionManager::GetInstance()->GetListOfColliders())
	{
		instance->spriteBatch.Draw(collisionManager, TextureManager::GetInstance()->GetTexture("debug"), tint);
	}*/

	// End the current spriteBatch
	instance->spriteBatch.End();

	// Render the spriteBatch
	instance->spriteBatch.RenderBatches();

	// Enable the use of the UI shader
	instance->uiShaderProgram.Use();

	// Feed the orthographic matrix into the uniform projection matrix (this is done for the purposes of normalizing the coordinates to the pixels
	GLint cameraTransformation = Game::GetInstance()->uiShaderProgram.GetUniformLocation("projectionMatrix");
	glm::mat4 orthographicMatrix = MainCamera.GetOrthoMatrix();
	glUniformMatrix4fv(cameraTransformation, 1, GL_FALSE, &(orthographicMatrix[0][0]));

	// Begin the sprite batch
	instance->spriteBatch.Begin(QuadSortType::TEXTURE);

	// Draw all of the UI elements
	for (UIElement* const element : uiElements)
	{
		instance->spriteBatch.Draw(element, element->GetTint());
	}
	
	// Stop the spriteBatch
	instance->spriteBatch.End();

	// Render the spriteBatch
	instance->spriteBatch.RenderBatches();

	// If the game has ended, change the display position of the final score
	gameEnded ? 
		TextureManager::GetInstance()->WriteText("Your final score: " + to_string(score), glm::vec2(0, -200), Color(0, 0, 0, 255)) : 
		TextureManager::GetInstance()->WriteText("Score: " + to_string(score), glm::vec2(-MainCamera.GetScreenDimensions().x + 10, MainCamera.GetScreenDimensions().y - 100), Color(255, 255, 255, 255));

	// Swap the buffers at the end of the render step
	SDL_GL_SwapWindow(t_window);
}

void Game::Render()
{
}

void Game::AddScore()
{
	score += 100;
}

void Game::AddScore(int t_score)
{
	score += t_score;
}

// Updates detatched from timing (frame based)
void Game::Update()
{
	// Update all of the necessary coroutine managers
	CoroutineManager<bool>::Update();

	// Update the collision manager
	CollisionManager::GetInstance()->Update();
}

void Game::Update(float t_delta_time)
{
	// Update the input manager at the beginning of each frame with the information of delta time
	InputHandler::GetInstance()->Update(true, t_delta_time);

	// Update all of the game objects in the scene
	for (vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update();
		(*it)->Update(t_delta_time);
	}

	// If the main camera has been moved and needs updating, update the main camera transformation matrix
	MainCamera.Update();

	// Trach the frames and timing (currently inaccurate)
	this->frames++;
	this->runTime += t_delta_time;
	this->framerate = frames / runTime;

	if(runTime > 1)
	{
		runTime -= 1;
		frames = 1;
	}

	// At the end of the frame, clear all necessary garbage
	GarbageDestroyer<Collider*>::GetInstance()->ClearGarbage();
	GarbageDestroyer<Character*>::GetInstance()->ClearGarbage();
	GarbageDestroyer<UIElement*>::GetInstance()->ClearGarbage();
}

void Game::EndGame(Collider* t_first_collider, Collider* t_second_collider)
{
	// The game has ended, so set the flag
	gameEnded = true;

	// Show the end screen
	uiElements.push_back(new UIElement(TextureManager::GetInstance()->GetTexture("title"), glm::vec2(0.0f, 0.0f), glm::vec2(MainCamera.GetScreenDimensions()), false));

	// Write the scores to the scores file, appending to the last results
	ofstream scoresFile;
	scoresFile.open("Saved Data/scores.txt", ios::app);
	scoresFile << score << endl;
	scoresFile.close();
}

float Game::GetElapsedSeconds()
{
	// If this is the first frame, the game is still initializing, so don't set the time yet. Otherwise, set it to the SDL ticks
	const float currentTime = gameStarted ? SDL_GetTicks() : gameStarted = true;

	// Calculate how much time has passed in miliseconds from the last frame
	const float seconds = (currentTime - lastTime) / (60 * 10);

	// Set the last time to the current one
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
