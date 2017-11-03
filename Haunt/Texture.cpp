/*
=================
Texture.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the Texture class
=================
*/
#include "Texture.h"
using namespace std;
/*
=================
- Data constructor initializes the OpenGL Texture ID object
- Is always called, thus ensures all OpenGL Texture ID objects are in a consistent state.
=================
*/
Texture::Texture()
{
	Texture::sdlTextureID = NULL;
}
/*
=================
- Data constructor initializes the OpenGL Texture ID object
- Is always called, thus ensures all OpenGL Texture ID objects are in a consistent state.
* @param fileName The image file to load
=================
*/
Texture::Texture(LPCSTR fileName, SDL_Renderer *renderer)
{
	Texture::loadTexture(fileName, renderer);
}

/*
=================
- Destructor.
=================
*/
Texture::~Texture()
{
	delete this;
}

int Texture::getIndex()
{
	return this->index;
}

void Texture::setIndex(int index)
{
	this->index = index;

	cout << "Texture index set to " << this->index << endl;
}

/*
=================
- create the texture for use.
=================
*/
bool Texture::loadTexture(LPCSTR fileName, SDL_Renderer *renderer) 	// create the texture for use.
{

	// Call SDL_Image IMG_LoadTexture to create the desired texture
	sdlTextureID = IMG_LoadTexture(renderer, fileName);

	// Check the Texture has been created from the surface
	if (sdlTextureID != 0)
	{
		cout << "Texture '" << fileName << "' successfully loaded." << endl;
		SDL_QueryTexture(sdlTextureID, NULL, NULL, &textureWidth, &textureHeight); // determine the width an height of the texture
		return true;
	}
	else
	{
		cout << "Texture '" << fileName << "' could not be loaded!!" << endl;
		cout << SDL_GetError() << endl;
	}

	return false;
}
/*
=================
- return the texture.
=================
*/
SDL_Texture* Texture::getTexture()        // return the texture.
{
	return Texture::sdlTextureID;
}

/*
=================
- Return width of texture.
=================
*/
int Texture::getTWidth() 						// Return width of texture;
{
	return textureWidth;
}
/*
=================
- Return height of texture.
=================
*/
int Texture::getTHeight() 						// Return height of texture;
{
	return textureHeight;
}
/*
=================
- Render the texture.
=================
*/
void Texture::renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect, Vector2D scaling)
{
	//SDL_RenderSetScale(renderer, scaling.X, scaling.Y);
	SDL_RenderCopy(renderer, texture, sourceRect, destinationRect);
}

void Texture::renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect, double rotationAngle, SDL_Point* spriteCentre, Vector2D scaling)
{
	//SDL_RenderSetScale(renderer, scaling.X, scaling.Y);
	SDL_RenderCopyEx(renderer, texture, sourceRect, destinationRect, rotationAngle, spriteCentre, SDL_FLIP_NONE);
}


