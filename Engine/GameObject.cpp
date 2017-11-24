#include "GameObject.h"

// Constructors (all require a texture for the sprite)
GameObject::GameObject(GLuint* t_texture_to_use)
{
	position.X = 0;
	position.Y = 0;

	/*this->sprite.SetTexture(t_texture_to_use);
	SDL_Point newCentre;
	newCentre.x = this->sprite.GetTexture()->GetTWidth() / 2;
	newCentre.y = this->sprite.GetTexture()->GetTHeight() / 2;
	this->sprite.SetSpriteCentre(newCentre);*/
}

GameObject::GameObject(GLuint* t_texture_to_use, const Vector2D t_new_position)
{
	position = t_new_position;

	//this->sprite.SetTexture(t_texture_to_use);
}

GameObject::GameObject(GLuint* t_texture_to_use, const Vector2D t_new_position, const float t_new_rotation)
{
	position = t_new_position;
	rotation = t_new_rotation;

	//this->sprite.SetTexture(t_texture_to_use);
}

GameObject::GameObject(GLuint* t_texture_to_use, const Vector2D t_new_position, const Vector2D t_new_scale)
{
	position = t_new_position;

	/*this->sprite.SetTexture(t_texture_to_use);
	this->scale = t_new_scale;
	this->sprite.SetSpriteScale(scale);
	this->sprite.ScaleSprite();*/
}

GameObject::GameObject(GLuint* t_texture_to_use, const Vector2D t_new_position, const Vector2D t_new_scale, const float t_new_rotation)
{
	position = t_new_position;
	rotation = t_new_rotation;

	/*this->sprite.SetTexture(t_texture_to_use);
	this->scale = t_new_scale;
	this->sprite.SetSpriteScale(t_new_scale);
	this->sprite.ScaleSprite();*/
}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(const Vector2D t_new_position)
{
	// Set the position to the passed new Vector2D
	this->position = t_new_position;
}

void GameObject::SetRotation(const float t_new_rotation)
{
	// Set the rotation to the passed new float value
	this->rotation = t_new_rotation;
}

void GameObject::SetScale(const Vector2D t_new_scale)
{
	// Set the scale to the passed new Vector2D value
	this->scale = t_new_scale;
}

Vector2D GameObject::GetPosition() const
{
	// Return the current position of the object
	return this->position;
}

double GameObject::GetRotation() const
{
	// Return the current rotation value of the object
	return this->rotation;
}

Vector2D GameObject::GetScale() const
{
	// Return the current scale value of the object
	return this->scale;
}

void GameObject::Update()
{
	// This method would always be overwritten
}

void GameObject::Update(float t_delta_time)
{
	// This method would always be overwritten
}

void GameObject::Render() const
{
	// Transform the Vector2D information to an SDL rectangle and render it on the screen
	SDL_Rect newPosition;
	/*newPosition.x = this->position.X - this->sprite.GetSpriteCentre().x;
	newPosition.y = this->position.Y - this->sprite.GetSpriteCentre().y;
	newPosition.w = this->sprite.GetTexture()->GetTWidth();
	newPosition.h = this->sprite.GetTexture()->GetTHeight();

	this->sprite.Render(t_renderer, nullptr, &newPosition, this->rotation, &this->sprite.GetSpriteCentre(), this->scale);*/
}
