#include "GameObject.h"
#include "Camera2D.h"

Uint16 GameObject::gameObjectsInitialized = 0;

// Constructor which takes in a texture, position, depth and rotation
GameObject::GameObject(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_depth, const float t_new_order, const float t_new_rotation): rotation(t_new_rotation), texture(t_texture_to_use), position(t_new_position), id(gameObjectsInitialized), order(t_new_order), dimensions(glm::vec2(texture->GetTextureWidth(), texture->GetTextureHeight()))
{

	// A game object was created, so increase the value of the initialized game objects by one
	gameObjectsInitialized++;
}

// Game object destructor
GameObject::~GameObject()
{
}

void GameObject::SetPosition(const glm::vec2 t_new_position)
{
	// Set the position to the passed new Vector2D
	this->position = t_new_position;
}

void GameObject::SetRotation(const float t_new_rotation)
{
	// Set the rotation to the passed new float value
	this->rotation = t_new_rotation;
}

void GameObject::SetScale(const glm::vec2 t_new_scale)
{
	// Set the scale to the passed new Vector2D value
	this->scale = t_new_scale;
}

void GameObject::SetOrder(const float t_new_order)
{
	// Set the order to the passed float value
	order = t_new_order;
}

void GameObject::SetDepth(const float t_new_depth, const float* t_new_order)
{
	// Set the depth to the passed float value. If an order is also specified, use that instead of the depth for ordering the sprite on screen
	depth = t_new_depth;
	order = t_new_order != nullptr ? *t_new_order : t_new_depth;
}

void GameObject::SetDirection(Direction t_new_direction)
{
	// Set the current direction to the value specified
	currentDirection = t_new_direction;
}

glm::vec2 GameObject::GetPosition() const
{
	// Return the current position of the object
	return this->position;
}

// TODO: Should change it to use the Rect class
glm::vec4 GameObject::GetRect() const
{
	// Return the current position of the object and its dimensions
	return (dimensions.x != 0 && dimensions.y != 0) ? 
		glm::vec4(position.x, position.y, dimensions.x, dimensions.y) : 
		glm::vec4(position.x, position.y, texture->GetTextureWidth(), texture->GetTextureHeight());
}

double GameObject::GetRotation() const
{
	// Return the current rotation value of the object
	return this->rotation;
}

glm::vec2 GameObject::GetScale() const
{
	// Return the current scale value of the object
	return this->scale;
}

glm::vec2 GameObject::GetDimensions() const
{
	// Return the dimensions of the object
	return this->dimensions;
}

Texture* GameObject::GetTexture()
{
	// Return the reference to the texture used to display the object
	return this->texture;
}

float GameObject::GetOrder()
{
	// Return the display order of the object
	return order;
}

float GameObject::GetDepth()
{
	// Return the parallaxing depth of the object
	return depth;
}

Direction GameObject::GetDirection()
{
	// Return the direction the object is facing
	return currentDirection;
}

// Get the current value of the object velocity
glm::vec2 GameObject::GetVelocity() const
{
	return this->velocity;
}

// Get the current value of the object acceleration
glm::vec2 GameObject::GetAcceleration() const
{
	return acceleration;
}

// Set the current value of the object velocity
void GameObject::SetVelocity(const glm::vec2 t_new_velocity)
{
	this->velocity = t_new_velocity;
}


// Set the current value of the object acceleration
void GameObject::SetAcceleration(const glm::vec2 t_new_acceleration)
{
	this->acceleration = t_new_acceleration;
}

void GameObject::Update()
{
	// This method would always be overwritten
}

void GameObject::Update(float t_delta_time)
{
	// This method would always be overwritten
}

// Check if the object is on screen relative to the camera specified
bool GameObject::IsOnScreen(Camera2D* t_main_camera) const
{
	if (abs((abs(position.x) + texture->GetTextureWidth()/2) - t_main_camera->GetPosition().x) < t_main_camera->GetScreenDimensions().x / 2)
	{
		return true;
	}
	
	return false;
}
