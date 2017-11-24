#include "Errors.h"

#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

void fatalError(std::string t_error_string)
{
	std::cout << t_error_string << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}
