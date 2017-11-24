/*
==================================================================================
cSDL2WNDManager.cpp
==================================================================================
*/
#include "WindowManager.h"
#include <GL/glew.h>
#include "Errors.h"

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
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fatalError("Failed to init SDL\n");
		return false;
	}

	// Set SDL OpenGL attributes to use a double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	mainWindow = SDL_CreateWindow(t_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                              t_width, t_height, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!mainWindow)
	{
		fatalError("Unable to create window\n");
		CheckSdlError(__LINE__);
		return false;
	}

	// Initialise the OpenGL Context
	mainContext = SDL_GL_CreateContext(mainWindow);

	if (mainContext == nullptr)
	{
		fatalError("GL Context failed to initialise");
		return false;
	}
	else
	{
		cout << ("Context created successfully") << endl;
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew");
	}

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

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