/*
==================================================================================
cSDL2WNDManager.cpp
==================================================================================
*/
#include "WindowManager.h"

WindowManager* WindowManager::instance = nullptr;


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
WindowManager* WindowManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new WindowManager();
	}
	return instance;
}

/*
=================================================================================
* Initialise the SDL Context with desired Window Title String, width and height
* @param windowTitle The Window Title String
* @param width The width of the window to draw
* @param height The height of the window to draw
=================================================================================
*/
bool WindowManager::InitializeWindow(string t_window_title, const int t_width, const int t_height)
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Failed to init SDL\n";
		return false;
	}

	mainWindow = SDL_CreateWindow(t_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                              t_width, t_height, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!mainWindow)
	{
		cout << "Unable to create window\n";
		CheckSdlError(__LINE__);
		return false;
	}
	// Get the renderer
	renderer = SDL_CreateRenderer(mainWindow, -1, 0);

	if (renderer != nullptr)
	{
		cout << "Renderer creation succeeded" << endl;

		SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
	}
	else
	{
		cout << "Renderer creation failed" << endl;
		return false;
	}

	return true;
}

void WindowManager::CheckSdlError(const int t_line = -1)
{
	const string error = SDL_GetError();

	if (error != "")
	{
		cout << "SDL Error : " << error << endl;

		if (t_line != -1)
			cout << "\nLine : " << t_line << endl;

		SDL_ClearError();
	}
}


SDL_Window* WindowManager::GetWindow() const
{
	return mainWindow;
}

SDL_GLContext WindowManager::GetOpenGlContext() const
{
	return mainContext;
}

SDL_Renderer* WindowManager::GetSdlRenderer() const
{
	return renderer;
}
