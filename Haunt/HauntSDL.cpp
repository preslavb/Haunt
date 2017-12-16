#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

// SDL2 Headers
#include <SDL/SDL.h>

#include <Engine/WindowManager.h>
#include "Game.h"
#include <GL/freeglut_std.h>

using namespace std;

//This is the SDL window
static WindowManager* windowManager = WindowManager::GetInstance();

//This is the our Game
static Game* game = Game::GetInstance();

// The main function
int main(int argc, char* argv[])
{
	// Initialize glut with the arguments for the main function
	glutInit(&argc, argv);

	// Initialize the window
	if (!windowManager->InitializeWindow(_WINDOW_TITLE, _WINDOW_WIDTH, _WINDOW_HEIGHT))
		// If the initialization fails, close out of the main function with an error
		return -1;

	// Initialize the game
	game->Initialise(windowManager->GetWindow());

	// Run the game loop
	game->Run(windowManager->GetWindow());

	// Clean the game data and exit
	game->CleanUp(windowManager->GetWindow());

	return 0;
}
