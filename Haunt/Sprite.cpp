/*
=================
Sprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "Sprite.h"
/*
=================
- Data constructor initializes the Sprite to the data passed to
- the constructor from the paramater position.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
Sprite::Sprite() 			// Default constructor
{

	this->spritePosition = { 0, 0, 0, 0 };
	this->spriteTexture = NULL;
	this->spriteCentre = {0, 0};
	this->spriteScale = { 1, 1 };
	this->spriteRotationAngle = 0;
}

Sprite::Sprite(Texture* theSpriteTexture) 			// Default constructor
{
	this->spriteTexture = theSpriteTexture;
	this->setSpriteDimensions(this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight());
	this->spritePosition = { 0, 0, this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight() };
	this->spriteCentre = { this->spritePosition.w / 2, this->spritePosition.h / 2};
	this->spriteScale = { 1, 1 };
	this->spriteRotationAngle = 0;
}

/*
=================
- Destructor
=================
*/
Sprite::~Sprite()			// Destructor
{
}
/*
=================
- Return the sprites current position.
=================
*/

SDL_Rect Sprite::getSpritePosition()  // Return the sprites current position
{
	return this->spritePosition;
}

/*
=================
- set the position of the sprite.
=================
*/

void Sprite::setSpritePosition(SDL_Point position)  // set the position of the sprite
{
	this->spritePosition.x = position.x;
	this->spritePosition.y = position.y;
}

/*
=================
- Return the sprites current image.
=================
*/

Texture* Sprite::getTexture()  // Return the sprites current image
{
	return this->spriteTexture;
}

/*
=================
- set the image of the sprite.
=================
*/

void Sprite::setTexture(Texture* theSpriteTexture)  // set the image of the sprite
{
	this->spriteTexture = theSpriteTexture;
	this->setSpriteDimensions(spriteTexture->getTWidth(), spriteTexture->getTHeight());
	this->spritePosition.w = textureWidth;
	this->spritePosition.h = textureHeight;
	this->spriteCentre = { this->spritePosition.w / 2, this->spritePosition.h / 2 };
}


void Sprite::render(SDL_Renderer* renderer, SDL_Rect* sourceRect, SDL_Rect* destinationRect, Vector2D scaling)
{
	this->spriteTexture->renderTexture(renderer, this->spriteTexture->getTexture(), sourceRect, destinationRect, scaling);
}

void Sprite::render(SDL_Renderer* renderer, SDL_Rect* sourceRect, SDL_Rect* destinationRect, double rotationAngle, SDL_Point* spriteCentre, Vector2D scaling)
{
	this->spriteTexture->renderTexture(renderer, this->spriteTexture->getTexture(), sourceRect, destinationRect, rotationAngle, spriteCentre, scaling);
}
/*
=================
- Set the sprite dimensions.
=================
*/
void Sprite::setSpriteDimensions(int textureWidth, int textureHeight)
{
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;
	this->spriteDimensions = { 0, 0, textureWidth, textureHeight };
}

/*
=================
- Get the sprite dimensions.
=================
*/
SDL_Rect Sprite::getSpriteDimensions()
{
	return this->spriteDimensions;
}
/*
=================
- Return the sprite centre.
=================
*/

SDL_Point Sprite::getSpriteCentre()  // Return the sprites current position
{
	return this->spriteCentre;
}

/*
=================
- set the the sprite centre.
=================
*/

void Sprite::setSpriteCentre(SDL_Point centre)  // set the position of the sprite
{
	this->spriteCentre.x = centre.x;
	this->spriteCentre.y = centre.y;
}
/*
=================
- Return the sprite scaling.
=================
*/

Vector2D Sprite::getSpriteScale()  // Return the sprites current scaling
{
	return this->spriteScale;
}

/*
=================
- set the the sprite scale.
=================
*/

void Sprite::setSpriteScale(Vector2D scale)  // set the sprites current scaling
{
	this->spriteScale.X += scale.X;
	this->spriteScale.Y += scale.Y;
}
/*
=================
- Update sprite scale.
=================
*/

void Sprite::scaleSprite()  // set the sprites current scaling
{
	// Scale sprite
	this->spritePosition.w = this->spriteDimensions.w * this->spriteScale.X;
	this->spritePosition.h = this->spriteDimensions.h * this->spriteScale.Y;
	// Scale Sprite Centre for rotation.
	this->spriteCentre.x = this->spritePosition.w / 2;
	this->spriteCentre.y = this->spritePosition.h / 2;
}
/*
=================
- Return the sprite rotation Angle.
=================
*/

float Sprite::getSpriteRotationAngle()  // Return the sprites current scaling
{
	return this->spriteRotationAngle;
}

/*
=================
- set the the sprite scale.
=================
*/

void Sprite::setSpriteRotationAngle(float angle)  // set the sprites current scaling
{
	this->spriteRotationAngle = angle;
}