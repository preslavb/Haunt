#pragma once
#include <glm/detail/type_vec2.hpp>
#include "Rect.h"
#include <unordered_map>

// Forward declaration of the collision class
struct Collision;
// Forward declaration of the game object class
class GameObject;

// The different types of collision two colliders can have between each other
enum class CollisionState
{
	None,
	Entered,
	Colliding,
	Escaped
};

// The Collider class (only axis aligned bounding boxes used)
[event_source(native)]
class Collider
{
private:
	// The bounding box of the collider
	Rect boundingBox;
	// The game object this collider belongs to
	GameObject* belongsTo;

	// The map of collision states between this collider and any other relevant colliders (could be more optimised)
	std::unordered_map<Collider*, CollisionState> collisionsMap;

	// The position of the collider itself and its offset from the origin of the game object it is attached to
	glm::vec2 position;
	glm::vec2 offset;

	// The distance to check for collisions
	float collisionDistance = 0;
public:
	// Constructor and destructor
	Collider(glm::vec2 t_position, Rect t_bounding_box, GameObject* t_belonging_to);
	~Collider();

	// Test whether a collision has taken place between the two colliders and register a collision between them.
	// Skip the calculation and go straight to the execution if the other collider already calculated a collision
	bool TestCollision(Collider* t_other_collider, bool t_already_checked = false);

	// The function determining which events should fire based on the collision state
	void HandleCollisions(Collider* t_other_collider, Collision* t_collision);

	// Accessors
	glm::vec2 GetPosition();
	glm::vec2 GetOffset();
	Rect GetRect();
	void SetRect(Rect t_new_rect);
	glm::vec2 GetDimensions();
	GameObject* GetObjectBelongingTo();
	CollisionState GetCollisionState(Collider* t_other_collider);
	void SetCollisionState(Collider* t_other_collider, CollisionState t_collision_state);
	float GetCollisionDistance();
	void SetPosition(glm::vec2 t_new_position);
	void SetCollisionDistance(float t_new_distance);

	// The events that fire for the different collision states
	__event void OnCollision(Collider* t_other_collider, Collider* t_event_collider);
	__event void DuringCollision(Collider* t_other_collider, Collider* t_event_collider);
	__event void OnEscape(Collider* t_other_collider, Collider* t_event_collider);
};

// The class containing information for the collision state between two colliders
struct Collision
{
	Collision(Collider* t_first_collider, Collider* t_second_collider, CollisionState t_collision_state) : FirstCollider(t_first_collider), SecondCollider(t_second_collider), State(t_collision_state)
	{
	}

	// The colliders the collision happened between
	Collider* FirstCollider;
	Collider* SecondCollider;

	// The state of the collision
	CollisionState State;
};