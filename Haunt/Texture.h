#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameConstants.h"
#include "Vector2D.h"

class Texture
{
private:
	SDL_Texture* sdlTextureId;
	int textureWidth;
	int textureHeight;
	int index;

public:
	Texture();
	Texture(LPCSTR t_file_name, SDL_Renderer* t_renderer);
	~Texture();
	int GetIndex() const;
	void SetIndex(int t_index);
	bool LoadTexture(LPCSTR t_file_name, SDL_Renderer* t_renderer);
	static void RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect);
	static void RenderTexture(SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect,
	                   double t_rotation_angle, SDL_Point* t_sprite_centre, Vector2D t_scaling);
	SDL_Texture* GetTexture() const;
	int GetTWidth() const;
	int GetTHeight() const;
};
#endif
