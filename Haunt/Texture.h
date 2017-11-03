#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameConstants.h"

class Texture
{
private:
	SDL_Texture* sdlTextureID;
	int textureWidth;
	int textureHeight;
	int index;

public:
	Texture();
	Texture(LPCSTR fileName, SDL_Renderer *renderer);
	~Texture();
	int getIndex();
	void setIndex(int index);
	bool loadTexture(LPCSTR fileName, SDL_Renderer *renderer);
	void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect, Vector2D scaling);
	void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect, double rotationAngle, SDL_Point* spriteCentre, Vector2D scaling);
	SDL_Texture* getTexture();
	int getTWidth();
	int getTHeight();
};
#endif