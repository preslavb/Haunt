#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <glm/glm.hpp>
#include "Texture.h"

class SpriteBatch;

// Any object present in the game
class GameObject
{
protected:
	// The position of the object represented by a Vector2D
	glm::vec2 position;
	// The scale of the object represented by a Vector2D
	glm::vec2 scale;
	// The rotation of the object represented by a double in radians
	double rotation;
	// The texture that represents this object in the scene
	Texture* texture;
public:
	// Constructors
	GameObject(Texture* t_texture_to_use);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale, float t_new_rotation);
	virtual ~GameObject();

	// Accessors for the position, rotation and scale of the object
	void SetPosition(glm::vec2 t_new_position);
	void SetRotation(float t_new_rotation);
	void SetScale(glm::vec2 t_new_scale);
	glm::vec2 GetPosition() const;
	double GetRotation() const;
	glm::vec2 GetScale() const;
	Texture* GetTexture();
	glm::vec4 GameObject::GetRect() const;

	// Update logic for any object in the game
	virtual void Update();

	// Update logic for any object in the game that is based on time passage
	virtual void Update(float t_delta_time);

	// Render the object sprite on screen
	void Render(SpriteBatch* t_sprite_batch) const;
};

#endif
