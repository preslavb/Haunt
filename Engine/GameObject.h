#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <glm/glm.hpp>
#include "Texture.h"
#include "Camera2D.h"

// Forward declare the spritebatch class for use in Game Object
class SpriteBatch;

// The directions the object could face (used by the renderer to flip textures)
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
	// The type string, used to identify what kind of item this is (mostly for collisions)
	string type = "GameObject";
	// The total number of game objects initialized
	static Uint16 gameObjectsInitialized;

	// The position of the object represented by a Vector2
	glm::vec2 position;
	// The scale of the object represented by a Vector2 (currently unused)
	glm::vec2 scale;
	// The rotation of the object represented by a double in radians (currently unused)
	double rotation;
	// A pointer to the texture that represents this object in the scene
	Texture* texture;

	// Acceleration applied to velocity and incremented each frame
	glm::vec2 acceleration;

	// Current velocity of the object
	glm::vec2 velocity;

	// The dimensions of the object (for representation on the screen, not for collisions)
	glm::vec2 dimensions;

	// The direction the object is facing (used for flipping characters based on walking direction)
	Direction currentDirection = Direction::Right;

	// The order the object should be displayed (like a layers system)
	float order;
	// A depth value for parallaxing (also used for the order value if none is specified) 
	float depth;	
public:
	// The unique ID for every object
	Uint16 id;

	// Constructor and destructor
	GameObject(Texture* t_texture_to_use, const glm::vec2 t_new_position = glm::vec2(0.0f, 0.0f), const float t_new_depth = 1, const float t_new_order = 1, const float t_new_rotation = 0.0f);
	virtual ~GameObject();

	// Accessors for the different properties of the object
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
	string GetType() const { return this->type; }
	void SetType(string t_new_type) { type = t_new_type; }

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
};

// Specify a way to feed a string with the game object
inline std::ostream & operator<<(std::ostream & t_string, GameObject const & t_object)
{
	t_string << t_object.id;
	return t_string;
}

#endif
