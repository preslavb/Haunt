#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameConstants.h"
#include <GL/glew.h>
#include <SDL/SDL_image.h>
#include "Errors.h"
#include <glm/glm.hpp>
#include "Vertex.h"
#include "Coroutine.h"

// Texture class to store the sdl surface and convert it to the GL texture ID. No more than one should be stored for each texture used in the game.
class Texture
{
private:
	// The SDL surface loaded by SDL_image
	SDL_Surface* sdlTextureId;
	// The converted GL texture ID to be used when rendering with OpenGL
	GLuint glTextureId;

	// The tint applied to the texture (depricated I think)
	Color tint;

	// The dimensions of the texture
	int width;
	int height;
public:
	// Default constructor. The texture needs to be loaded if this one is used
	Texture();
	// Constructor which automatically loads the texture given in the argument
	Texture(LPCSTR t_file_name);
	// Destructor
	~Texture();

	// Load the texture and return a bool for whether or not the texture was loaded successfully
	bool LoadTexture(LPCSTR t_file_name);

	// Returns the OpenGL Texture ID
	GLuint* GetTextureID();

	// Return the dimensions of the loaded texture
	int GetTextureWidth() const;
	int GetTextureHeight() const;
};
#endif
