#pragma once
#include <vector>
#include "Collider.h"

// The default distance that two colliders need to be from each other for collision checking to occur (this should be overwritten when using big objects, preferably by the value of half the diagonal of the bounding box)
static float const COLLISION_CHECKING_DISTANCE = 200.0f;

// The collision manager class, which handles when collision events are fired and stores all available colliders
class CollisionManager
{
private:
	// The private constructors for the collision manager (private so that it can only be instantiated by the GetInstance method)
	CollisionManager();
	~CollisionManager();

	// The instance of the collision manager (singleton)
	static CollisionManager* instance;
	std::list<Collider*> registeredColliders;
	std::list<Collision*> registeredCollisions;
public:
	// Static method to return the instance of the singleton CollisionManager
	static CollisionManager* GetInstance();

	// Register a collider to be checked for collision against other objects
	void RegisterCollider(Collider* t_collider);

	// Register a collision that happened between two colliders (returns false if the collision was already registered this frame by the other collider)
	bool RegisterCollision(Collision* t_collision);

	// Check for collisions between two different colliders and return a collision if they intersect
	Collision* CheckCollision(Collider* t_first_collider, Collider* t_second_collider);

	// Remove a collider from the list of colliders to check
	void UnregisterCollider(Collider* t_collider);

	// Collision manager update logic
	void Update();

	// Accessor to the list of colliders
	std::list<Collider*>* GetListOfColliders();
};

