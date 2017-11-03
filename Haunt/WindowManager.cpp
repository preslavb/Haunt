/*
==================================================================================
cSDL2WNDManager.cpp
==================================================================================
*/
#include "WindowManager.h"

WindowManager* WindowManager::instance = NULL;


/*
=================================================================================
Constructor
=================================================================================
*/
WindowManager::WindowManager()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
WindowManager* WindowManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new WindowManager();
	}
	return WindowManager::instance;
}

/*
=================================================================================
* Initialise the SDL Context with desired Window Title String, width and height
* @param windowTitle The Window Title String
* @param width The width of the window to draw
* @param height The height of the window to draw
=================================================================================
*/
bool WindowManager::initializeWindow(string windowTitle, int width, int height)
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Failed to init SDL\n";
		return false;
	}

	mainWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!mainWindow)
	{
		cout << "Unable to create window\n";
		checkSDLError(__LINE__);
		return false;
	}
	else
	{
		// Get the renderer
			renderer = SDL_CreateRenderer(mainWindow, -1, 0);

			if (renderer != 0)
			{
				std::cout << "Renderer creation succeeded" << std::endl;

				SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
			}
			else
			{
				std::cout << "Renderer creation failed" << std::endl;
				return false;
			}
	}

	return true;
}

void WindowManager::checkSDLError(int line = -1)
{
	string error = SDL_GetError();

	if (error != "")
	{
		cout << "SDL Error : " << error << std::endl;

		if (line != -1)
			cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}


SDL_Window* WindowManager::getWindow()
{
	return mainWindow;
}

SDL_GLContext WindowManager::getOpenGLContext()
{
	return mainContext;
}

SDL_Renderer* WindowManager::getSDLRenderer()
{
	return renderer;
}