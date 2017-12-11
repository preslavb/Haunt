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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	if (!windowManager->InitializeWindow(_WINDOW_TITLE, _WINDOW_WIDTH, _WINDOW_HEIGHT))
		return -1;

	game->Initialise(windowManager->GetWindow());

	game->Run(windowManager->GetWindow());

	game->CleanUp(windowManager->GetWindow());

	return 0;
}
