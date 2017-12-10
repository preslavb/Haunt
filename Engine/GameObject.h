#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <glm/glm.hpp>
#include "Texture.h"
#include "Camera2D.h"

class SpriteBatch;

enum Direction
{
	Left,
	Right,
	Up,
	Down
};

// Any object present in the game
class GameObject
{
protected:
	static Uint16 gameObjectsInitialized;

	// The position of the object represented by a Vector2D
	glm::vec2 position;
	// The scale of the object represented by a Vector2D
	glm::vec2 scale;
	// The rotation of the object represented by a double in radians
	double rotation;
	// The texture that represents this object in the scene
	Texture* texture;

	// Acceleration applied to velocity and incremented each frame
	glm::vec2 acceleration;

	// Current velocity of the object
	glm::vec2 velocity;

	glm::vec2 dimensions;

	Direction currentDirection = Direction::Right;

	float order;

	float depth;

	string type = "GameObject";
public:
	Uint16 id;

	// Constructors
	GameObject(Texture* t_texture_to_use);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale);
	GameObject(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale, float t_new_rotation);
	virtual ~GameObject();

	// Accessors for the position, rotation and scale of the object
	virtual void SetPosition(glm::vec2 t_new_position);
	void SetRotation(float t_new_rotation);
	void SetScale(glm::vec2 t_new_scale);
	void SetOrder(const float t_new_order);
	void SetDepth(const float t_new_depth, const float* t_new_order = nullptr);
	void SetDirection(Direction t_new_direction);
	glm::vec2 GetPosition() const;
	double GetRotation() const;
	glm::vec2 GetScale() const;
	glm::vec2 GetDimensions() const;
	Texture* GetTexture();
	float GetOrder();
	float GetDepth();
	Direction GetDirection();
	glm::vec4 GameObject::GetRect() const;

	string GetType() { return type; }

	// Accessors to velocity and acceleration
	glm::vec2 GetVelocity() const;
	glm::vec2 GetAcceleration() const;
	void SetVelocity(glm::vec2 t_new_velocity);
	void SetAcceleration(glm::vec2 t_new_acceleration);

	// Update logic for any object in the game
	virtual void Update();

	// Update logic for any object in the game that is based on time passage
	virtual void Update(float t_delta_time);
	bool IsOnScreen(Camera2D* t_main_camera) const;

	// Render the object sprite on screen
	void Render(SpriteBatch* t_sprite_batch) const;
};

inline std::ostream & operator<<(std::ostream & t_string, GameObject const & t_object)
{
	t_string << t_object.id;
	return t_string;
}

#endif
