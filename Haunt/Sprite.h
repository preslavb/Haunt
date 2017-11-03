#ifndef _SPRITE_H
#define _SPRITE_H

#include "TextureManager.h"
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
	Sprite(Texture* theSpriteTexture);
	~Sprite();
	void render(SDL_Renderer* renderer, SDL_Rect* sourceRect, SDL_Rect* destinationRect, Vector2D scaling);
	void render(SDL_Renderer* renderer, SDL_Rect* sourceRect, SDL_Rect* destinationRect, double rotationAngle, SDL_Point* spriteCentre, Vector2D scaling);
	SDL_Rect getSpritePosition();
	void setSpritePosition(SDL_Point position);
	Texture* getTexture();
	void setTexture(Texture* theSpriteTexture);
	void setSpriteDimensions(int textureWidth, int textureHeight);
	SDL_Rect getSpriteDimensions();
	SDL_Point getSpriteCentre();
	void setSpriteCentre(SDL_Point centre);
	Vector2D getSpriteScale();
	void setSpriteScale(Vector2D scale);
	void scaleSprite();
	float getSpriteRotationAngle();
	void setSpriteRotationAngle(float angle);
};
#endif