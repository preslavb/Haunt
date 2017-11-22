#ifndef _SPRITE_H
#define _SPRITE_H

#include "Texture.h"

// The 2D representation of a texture in the game
class Sprite
{
private:
	// Sprite position
	SDL_Rect spritePosition;
	SDL_Rect spriteDimensions;
	SDL_Point spriteCentre;
	Vector2D spriteScale;
	float spriteRotationAngle;

	// Pointer to the Sprite Texture
	Texture* spriteTexture;

	// Texture width & Height
	int textureWidth;
	int textureHeight;


public:
	Sprite();
	Sprite(Texture* t_the_sprite_texture);
	~Sprite();
	void Render(SDL_Renderer* t_renderer, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect) const;
	void Render(SDL_Renderer* t_renderer, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect, double t_rotation_angle,
	            SDL_Point* t_sprite_centre, Vector2D t_scaling) const;
	SDL_Rect GetSpritePosition() const;
	void SetSpritePosition(SDL_Point t_position);
	Texture* GetTexture() const;
	void SetTexture(Texture* t_the_sprite_texture);
	void SetSpriteDimensions(int t_texture_width, int t_texture_height);
	SDL_Rect GetSpriteDimensions() const;
	SDL_Point GetSpriteCentre() const;
	void SetSpriteCentre(SDL_Point t_centre);
	Vector2D GetSpriteScale() const;
	void SetSpriteScale(Vector2D t_scale);
	void ScaleSprite();
	float getSpriteRotationAngle() const;
	void SetSpriteRotationAngle(float t_angle);
};
#endif
