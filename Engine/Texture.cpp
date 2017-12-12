/*
=================
Texture.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the Texture class
=================
*/
#include "Texture.h"
#include "CoroutineManager.h"
#include "GarbageDestroyer.h"

using namespace std;

/*
=================
- Data constructor initializes the OpenGL Texture ID object
- Is always called, thus ensures all OpenGL Texture ID objects are in a consistent state.
=================
*/
Texture::Texture(): depth(1)
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
Texture::Texture(const LPCSTR t_file_name) : depth(1)
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
		std::cout << "Texture '" << t_file_name << "' successfully loaded. " << (int)sdlTextureId->format->BitsPerPixel << endl;

		GLuint glTexture;

		glGenTextures(1, &glTexture);

		glBindTexture(GL_TEXTURE_2D, glTexture);

		int mode = (int)sdlTextureId->format->BitsPerPixel == 32 ? GL_RGBA : GL_RGB;

		glTexImage2D(GL_TEXTURE_2D, 0, mode, sdlTextureId->w, sdlTextureId->h, 0, mode, GL_UNSIGNED_BYTE, sdlTextureId->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		this->glTextureId = glTexture;

		this->width = sdlTextureId->w;

		this->height = sdlTextureId->h;

		return true;
	}	
	
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

float Texture::GetDepth()
{
	return depth;
}

float Texture::GetOrder()
{
	return order;
}

void Texture::SetDepth(const float t_new_depth, const float* t_new_order)
{
	depth = t_new_depth;
	order = t_new_order != nullptr ? *t_new_order : t_new_depth;
}
