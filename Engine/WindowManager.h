#ifndef _WINDOWMANAGER_H
#define _WINDOWMANAGER_H

#include <SDL/SDL.h>
#include <string>
#include <iostream>

using namespace std;

// The manager for the Windows Window screen
class WindowManager
{
public:
	// Constructor
	WindowManager();

	// Initialisation of the window with a title, width and height
	bool InitializeWindow(string t_window_title, int t_width, int t_height);

	// Throw any errors that SDL might have encountered during creation of the window
	static void CheckSdlError(int t_line);

	// Get a reference to the window
	SDL_Window* GetWindow() const;

	// Returns the OpenGL Context
	SDL_GLContext GetOpenGlContext() const;

	// Singleton
	static WindowManager* GetInstance();

private:
	// The singleton instance of the Window Manager
	static WindowManager* instance;
	
	// The main window to render the game to
	SDL_Window* mainWindow;

	// The OpenGL context
	SDL_GLContext mainContext;
};

#endif
