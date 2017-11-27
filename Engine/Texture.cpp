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
	delete this;
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
		cout << "Texture '" << t_file_name << "' successfully loaded." << endl;

		GLuint glTexture;

		glGenTextures(1, &glTexture);

		glBindTexture(GL_TEXTURE_2D, glTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlTextureId->w, sdlTextureId->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlTextureId->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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
int Texture::GetTWidth() const
// Return width of texture;
{
	return sdlTextureId->clip_rect.w;
}

/*
=================
- Return height of texture.
=================
*/
int Texture::GetTHeight() const
// Return height of texture;
{
	return sdlTextureId->clip_rect.h;
}

/*
=================
- Render the texture.
=================
*/
void Texture::RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect,
							SDL_Rect* t_destination_rect)
{
	SDL_RenderCopy(t_renderer, t_texture, t_source_rect, t_destination_rect);
}

void Texture::RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect,
							SDL_Rect* t_destination_rect, const double t_rotation_angle, SDL_Point* t_sprite_centre, float t_scaling)
{
	SDL_RenderCopyEx(t_renderer, t_texture, t_source_rect, t_destination_rect, t_rotation_angle, t_sprite_centre, SDL_FLIP_NONE);
}
