#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameConstants.h"
#include "Vector2D.h"
#include <GL/glew.h>
#include <SDL/SDL_image.h>
#include "Errors.h"

class Texture
{
private:
	SDL_Surface* sdlTextureId;
	GLuint glTextureId;

	int width;
	int height;

public:
	Texture();
	Texture(LPCSTR t_file_name);
	~Texture();
	bool LoadTexture(LPCSTR t_file_name);
	static void RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect);
	static void RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect,
	                   double t_rotation_angle, SDL_Point* t_sprite_centre, Vector2D t_scaling);
	GLuint* GetTexture();
	int GetTWidth() const;
	int GetTHeight() const;
};
#endif
