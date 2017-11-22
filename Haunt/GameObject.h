#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "GameIncludes.h";

// Any object present in the game
class GameObject
{
protected:
	// The position of the object represented by a Vector2D
	Vector2D position;
	// The scale of the object represented by a Vector2D
	Vector2D scale;
	// The rotation of the object represented by a double in radians
	double rotation;
	// The sprite that represents this object in the scene
	Sprite sprite;
public:
	// Constructors
	GameObject(Texture* t_texture_to_use);
	GameObject(Texture* t_texture_to_use, Vector2D t_new_position);
	GameObject(Texture* t_texture_to_use, Vector2D t_new_position, float t_new_rotation);
	GameObject(Texture* t_texture_to_use, Vector2D t_new_position, Vector2D t_new_scale);
	GameObject(Texture* t_texture_to_use, Vector2D t_new_position, Vector2D t_new_scale, float t_new_rotation);
	virtual ~GameObject();

	// Accessors for the position, rotation and scale of the object
	void SetPosition(Vector2D t_new_position);
	void SetRotation(float t_new_rotation);
	void SetScale(Vector2D t_new_scale);
	Vector2D GetPosition() const;
	double GetRotation() const;
	Vector2D GetScale() const;

	// Update logic for any object in the game
	virtual void Update();

	// Update logic for any object in the game that is based on time passage
	virtual void Update(float t_delta_time);

	// Render the object sprite on screen
	void Render(SDL_Renderer* t_renderer) const;
};

#endif
