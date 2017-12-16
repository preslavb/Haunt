#include "stdafx.h"
#include "CollisionManager.h"
#include <glm/detail/func_geometric.inl>
#include <iostream>

// Initialize the instance to a null pointer
CollisionManager* CollisionManager::instance = nullptr;

// Default constructor for the collision manager
CollisionManager::CollisionManager()
{
}

// Default destructor for the collision manager
CollisionManager::~CollisionManager()
{
}

// Get instance of the singleton. If one does not exist, create it
CollisionManager* CollisionManager::GetInstance()
{
	if (!instance)
	{
		instance = new CollisionManager;
	}

	return instance;
}

void CollisionManager::RegisterCollider(Collider* t_collider)
{
	// Push the specified collider into the list of colliders to check
	registeredColliders.push_back(t_collider);

	// Debug information on when new colliders are registered
	std::cout << "Registered a new Collider, new size is: " << registeredColliders.size() << std::endl;
}

bool CollisionManager::RegisterCollision(Collision* t_collision)
{
	// Itterate through the already registered collisions. If an identical but opposite collision was found, drop the collision as it's already registered
	for (Collision* opposite : registeredCollisions)
	{
		if (opposite->FirstCollider == t_collision->SecondCollider && opposite->SecondCollider == t_collision->FirstCollider)
		{
			return false;
		}
	}

	// Otherwise, push the new collision object to the collisions list to be executed this frame
	registeredCollisions.push_back(t_collision);
	return true;
}

Collision* CollisionManager::CheckCollision(Collider* t_first_collider, Collider* t_second_collider)
{
	// Check all registered collisions. If an identical one is found (order doesn't need to match) return it
	for (Collision* opposite : registeredCollisions)
	{
		if ((opposite->FirstCollider == t_first_collider && opposite->SecondCollider == t_second_collider) ||
			(opposite->SecondCollider == t_first_collider && opposite->FirstCollider == t_second_collider))
		{
			return opposite;
		}
	}

	// Otherwise, return a null pointer
	return nullptr;
}

void CollisionManager::UnregisterCollider(Collider* t_collider)
{
	// Iterate through the list of colliders and erase the one that was specified
	for (std::list<Collider*>::iterator removeIt = registeredColliders.begin(); removeIt != registeredColliders.end(); ++removeIt)
	{
		if (*removeIt == t_collider)
		{
			registeredColliders.erase(removeIt);
			break;
		}
	}
}

void CollisionManager::Update()
{
	// Iterate through the list of registered colliders, and for each one, iterate through all the others
	for (std::list<Collider*>::const_iterator it = registeredColliders.begin(), end = registeredColliders.end() ; it != end; ++it)
	{
		for (std::list<Collider*>::const_iterator it2 = registeredColliders.begin(), end2 = registeredColliders.end(); it2 != end2; ++it2)
		{
			// If the colliders aren't the same one, the object they belong to isn't the same one and the distance between them is either shorter than the specified one or shorter than the default one
			// check for a collision between the objects
			if (it != it2 && 
				(*it)->GetObjectBelongingTo() != (*it2)->GetObjectBelongingTo() && 
				(glm::distance((*it)->GetPosition() + (*it)->GetRect().GetDimensions() / 2.0f, (*it2)->GetPosition() + (*it2)->GetRect().GetDimensions() / 2.0f) < COLLISION_CHECKING_DISTANCE ||
				glm::distance((*it)->GetPosition() + (*it)->GetRect().GetDimensions() / 2.0f, (*it2)->GetPosition() + (*it2)->GetRect().GetDimensions() / 2.0f) < (*it)->GetCollisionDistance()))
			{
				// If the nested collision returns true, the calculation for the first one can be skipped
				(*it)->TestCollision((*it2), (*it2)->TestCollision((*it)));
			}

			// Safety feature to make sure the iterator is still valid at the end of execution, shouldn't be needed with lists
			if (it2 == registeredColliders.end()) break;
		}
		// Safety feature to make sure the iterator is still valid at the end of execution, shouldn't be needed with lists
		if (it == registeredColliders.end()) break;
	}

	// Iterate through the registered collisions and handle them for each object involved
	while (!registeredCollisions.empty())
	{
		registeredCollisions.back()->FirstCollider->HandleCollisions(registeredCollisions.back()->SecondCollider, registeredCollisions.back());
		registeredCollisions.back()->SecondCollider->HandleCollisions(registeredCollisions.back()->FirstCollider, registeredCollisions.back());

		// The collision has been handled, so remove it
		registeredCollisions.pop_back();
	}
}

std::list<Collider*>* CollisionManager::GetListOfColliders()
{
	// Return a pointer to the list of registered colliders in the collision manager
	return &registeredColliders;
}
