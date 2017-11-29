#include "Errors.h"

#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

// Display a fatal error to the console and exit the application
void fatalError(const std::string t_error_string)
{
	std::cout << t_error_string << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}
