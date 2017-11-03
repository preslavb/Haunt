#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

// SDL2 Headers
#include <SDL.h>

#include "WindowManager.h"
#include "Game.h"

using namespace std;

//This is the SDL window
static WindowManager* windowManager = WindowManager::getInstance();

//This is the our Game
static Game* game = Game::getInstance();

int main(int argc, char *argv[])
{
	if (!windowManager->initializeWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT))
		return -1;

	game->initialise(windowManager->getWindow(), windowManager->getSDLRenderer());

	game->run(windowManager->getWindow(), windowManager->getSDLRenderer());

	game->cleanUp(windowManager->getWindow());

	return 0;
}