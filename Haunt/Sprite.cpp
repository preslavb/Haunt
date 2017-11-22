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
Sprite::Sprite() // Default constructor
{
	this->spritePosition = {0, 0, 0, 0};
	this->spriteTexture = nullptr;
	this->spriteCentre = {0, 0};
	this->spriteScale = {1, 1};
	this->spriteRotationAngle = 0;
}

Sprite::Sprite(Texture* theSpriteTexture) // Default constructor
{
	this->spriteTexture = theSpriteTexture;
	this->SetSpriteDimensions(this->spriteTexture->GetTWidth(), this->spriteTexture->GetTHeight());
	this->spritePosition = {0, 0, this->spriteTexture->GetTWidth(), this->spriteTexture->GetTHeight()};
	this->spriteCentre = {this->spritePosition.w / 2, this->spritePosition.h / 2};
	this->spriteScale = {1, 1};
	this->spriteRotationAngle = 0;
}

/*
=================
- Destructor
=================
*/
Sprite::~Sprite() // Destructor
{
}

/*
=================
- Return the sprites current position.
=================
*/

SDL_Rect Sprite::GetSpritePosition() const
// Return the sprites current position
{
	return this->spritePosition;
}

/*
=================
- set the position of the sprite.
=================
*/

void Sprite::SetSpritePosition(const SDL_Point t_position) // set the position of the sprite
{
	this->spritePosition.x = t_position.x;
	this->spritePosition.y = t_position.y;
}

/*
=================
- Return the sprites current image.
=================
*/

Texture* Sprite::GetTexture() const
// Return the sprites current image
{
	return this->spriteTexture;
}

/*
=================
- set the image of the sprite.
=================
*/

void Sprite::SetTexture(Texture* t_the_sprite_texture) // set the image of the sprite
{
	this->spriteTexture = t_the_sprite_texture;
	this->SetSpriteDimensions(spriteTexture->GetTWidth(), spriteTexture->GetTHeight());
	this->spritePosition.w = textureWidth;
	this->spritePosition.h = textureHeight;
	this->spriteCentre = {this->spritePosition.w / 2, this->spritePosition.h / 2};
}


void Sprite::Render(SDL_Renderer* t_renderer, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect) const
{
	this->spriteTexture->RenderTexture(t_renderer, this->spriteTexture->GetTexture(), t_source_rect, t_destination_rect);
}

void Sprite::Render(SDL_Renderer* t_renderer, SDL_Rect* t_source_rect, SDL_Rect* t_destination_rect, const double rotationAngle,
					SDL_Point* t_sprite_centre, const Vector2D t_scaling) const
{
	this->spriteTexture->RenderTexture(t_renderer, this->spriteTexture->GetTexture(), t_source_rect, t_destination_rect,
									   rotationAngle, t_sprite_centre, t_scaling);
}

/*
=================
- Set the sprite dimensions.
=================
*/
void Sprite::SetSpriteDimensions(const int t_texture_width, const int t_texture_height)
{
	this->textureWidth = t_texture_width;
	this->textureHeight = t_texture_height;
	this->spriteDimensions = {0, 0, t_texture_width, t_texture_height};
}

/*
=================
- Get the sprite dimensions.
=================
*/
SDL_Rect Sprite::GetSpriteDimensions() const
{
	return this->spriteDimensions;
}

/*
=================
- Return the sprite centre.
=================
*/

SDL_Point Sprite::GetSpriteCentre() const
// Return the sprites current position
{
	return this->spriteCentre;
}

/*
=================
- set the the sprite centre.
=================
*/

void Sprite::SetSpriteCentre(const SDL_Point t_centre) // set the position of the sprite
{
	this->spriteCentre.x = t_centre.x;
	this->spriteCentre.y = t_centre.y;
}

/*
=================
- Return the sprite scaling.
=================
*/

Vector2D Sprite::GetSpriteScale() const
// Return the sprites current scaling
{
	return this->spriteScale;
}

/*
=================
- set the the sprite scale.
=================
*/

void Sprite::SetSpriteScale(const Vector2D t_scale) // set the sprites current scaling
{
	this->spriteScale.X += t_scale.X;
	this->spriteScale.Y += t_scale.Y;
	ScaleSprite();
}

/*
=================
- Update sprite scale.
=================
*/

void Sprite::ScaleSprite() // set the sprites current scaling
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

float Sprite::getSpriteRotationAngle() const
// Return the sprites current scaling
{
	return this->spriteRotationAngle;
}

/*
=================
- set the the sprite scale.
=================
*/

void Sprite::SetSpriteRotationAngle(const float t_angle) // set the sprites current scaling
{
	this->spriteRotationAngle = t_angle;
}
