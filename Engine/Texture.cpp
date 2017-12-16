/*
=================
Texture.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the Texture class
=================
*/
#include "Texture.h"
#include "CoroutineManager.h"

using namespace std;

/*
=================
- Data constructor initializes the OpenGL Texture ID object
- Is always called, thus ensures all OpenGL Texture ID objects are in a consistent state.
=================
*/
Texture::Texture()
{
	sdlTextureId = nullptr;
}

/*
=================
- Data constructor initializes the OpenGL Texture ID object
- Is always called, thus ensures all OpenGL Texture ID objects are in a consistent state.
* @param fileName The image file to load
=================
*/
Texture::Texture(const LPCSTR t_file_name)
{
	LoadTexture(t_file_name);
}

/*
=================
- Destructor.
=================
*/
Texture::~Texture()
{
	//delete this;
}

/*
=================
- create the texture for use.
=================
*/
bool Texture::LoadTexture(const LPCSTR t_file_name) // create the texture for use.
{
	// Call SDL_Image IMG_LoadTexture to create the desired texture
	sdlTextureId = IMG_Load(t_file_name);

	// Check the Texture has been created from the surface
	if (sdlTextureId != nullptr)
	{
		// The texture has been safely loaded
		std::cout << "Texture '" << t_file_name << "' successfully loaded. " << (int)sdlTextureId->format->BitsPerPixel << endl;

		// Initialize the value to store the texture
		GLuint glTexture;

		// Generate a texture for the GL ID
		glGenTextures(1, &glTexture);

		// Bind the texture so that we may alter it
		glBindTexture(GL_TEXTURE_2D, glTexture);

		// Set the appropriate mode (this is important, otherwise the alpha chanel could be lost and cause severe distortion in the image)
		int mode = (int)sdlTextureId->format->BitsPerPixel == 32 ? GL_RGBA : GL_RGB;

		// Feed the pixels of the SDL surface to the newly created GL Texture, using the mode previously specified
		glTexImage2D(GL_TEXTURE_2D, 0, mode, sdlTextureId->w, sdlTextureId->h, 0, mode, GL_UNSIGNED_BYTE, sdlTextureId->pixels);

		// Make the texture tile if the UVs are not standard
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		// Make sure that standard UVs are clamped to the edge of the texture (causes a one pixel wrap around otherwise)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		// Set the magnifying and minifying functions for scaling of the texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Generate the mipmap for the texture (used for minifying)
		glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind the texture as it no longer needs to be altered
		glBindTexture(GL_TEXTURE_2D, 0);

		// Set the GL texture ID to be this one
		this->glTextureId = glTexture;

		// Set the dimensions based on the SDL surface dimensions
		this->width = sdlTextureId->w;
		this->height = sdlTextureId->h;

		// Return that the texture was created successfully
		return true;
	}	
	
	// The texture was not created successfully, so break out of the program with an error
	cout << "Texture '" << t_file_name << "' could not be loaded!!" << endl;

	cout << SDL_GetError() << endl;

	fatalError("Texture could not be loaded!!");

	return false;
}

/*
=================
- return the texture.
=================
*/
GLuint* Texture::GetTextureID()
// return the texture.
{
	return &glTextureId;
}

/*
=================
- Return width of texture.
=================
*/
int Texture::GetTextureWidth() const
// Return width of texture;
{
	return sdlTextureId->clip_rect.w;
}

/*
=================
- Return height of texture.
=================
*/
int Texture::GetTextureHeight() const
// Return height of texture;
{
	return sdlTextureId->clip_rect.h;
}