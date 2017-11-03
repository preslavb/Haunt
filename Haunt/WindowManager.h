#ifndef _WINDOWMANAGER_H
#define _WINDOWMANAGER_H

#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class WindowManager
{
public:
	WindowManager();

	bool initializeWindow(string windowTitle, int width, int height);
	void checkSDLError(int line);
	SDL_Window* getWindow();
	SDL_GLContext getOpenGLContext();
	SDL_Renderer* getSDLRenderer();

	static WindowManager* getInstance();

private:

	static WindowManager* instance;
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;
	SDL_Renderer* renderer;

};

#endif

