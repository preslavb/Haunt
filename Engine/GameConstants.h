#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

// Windows & SDL 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <SDL/SDL.h>
// Maths functions
#include <math.h>
#define _PI 3.14159265
#define _FRICTION 10
#define _GRAVITY 9.8
#define _METER 10.0f

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//Define the string to appear in the top left corner of the window and the window dimensions
#define _WINDOW_TITLE "Haunt"
#define _WINDOW_WIDTH 1024
#define _WINDOW_HEIGHT 768

inline extern float Compare(float t_first, float t_second)
{
	if (t_first < t_second)
	{
		return -1;
	}
	else if (t_first == t_second)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

#endif
