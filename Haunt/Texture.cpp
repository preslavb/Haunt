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
Texture::Texture(const LPCSTR t_file_name, SDL_Renderer* t_renderer)
{
	LoadTexture(t_file_name, t_renderer);
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

int Texture::GetIndex() const
{
	return this->index;
}

void Texture::SetIndex(const int t_index)
{
	this->index = t_index;

	cout << "Texture index set to " << this->index << endl;
}

/*
=================
- create the texture for use.
=================
*/
bool Texture::LoadTexture(const LPCSTR t_file_name, SDL_Renderer* t_renderer) // create the texture for use.
{
	// Call SDL_Image IMG_LoadTexture to create the desired texture
	sdlTextureId = IMG_LoadTexture(t_renderer, t_file_name);

	// Check the Texture has been created from the surface
	if (sdlTextureId != nullptr)
	{
		cout << "Texture '" << t_file_name << "' successfully loaded." << endl;
		SDL_QueryTexture(sdlTextureId, nullptr, nullptr, &textureWidth, &textureHeight);
		// determine the width an height of the texture
		return true;
	}
	cout << "Texture '" << t_file_name << "' could not be loaded!!" << endl;
	cout << SDL_GetError() << endl;

	return false;
}

/*
=================
- return the texture.
=================
*/
SDL_Texture* Texture::GetTexture() const
// return the texture.
{
	return sdlTextureId;
}

/*
=================
- Return width of texture.
=================
*/
int Texture::GetTWidth() const
// Return width of texture;
{
	return textureWidth;
}

/*
=================
- Return height of texture.
=================
*/
int Texture::GetTHeight() const
// Return height of texture;
{
	return textureHeight;
}

/*
=================
- Render the texture.
=================
*/
void Texture::RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect,
							SDL_Rect* t_destination_rect)
{
	//SDL_RenderSetScale(renderer, scaling.X, scaling.Y);
	SDL_RenderCopy(t_renderer, t_texture, t_source_rect, t_destination_rect);
}

void Texture::RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect,
							SDL_Rect* t_destination_rect, const double rotationAngle, SDL_Point* t_sprite_centre, Vector2D t_scaling)
{
	//SDL_RenderSetScale(renderer, scaling.X, scaling.Y);
	SDL_RenderCopyEx(t_renderer, t_texture, t_source_rect, t_destination_rect, rotationAngle, t_sprite_centre, SDL_FLIP_NONE);
}
