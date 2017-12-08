#include "stdafx.h"
#include "CollisionManager.h"
#include <glm/detail/func_geometric.inl>
#include <iostream>

CollisionManager* CollisionManager::instance = nullptr;

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

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
	registeredColliders.push_back(t_collider);
	std::cout << "Registered a new Collider, new size is: " << registeredColliders.size() << std::endl;
}

void CollisionManager::RegisterCollision(Collision* t_collision)
{
	for (Collision* opposite : registeredCollisions)
	{
		if (opposite->FirstCollider == t_collision->SecondCollider && opposite->SecondCollider == t_collision->FirstCollider)
		{
			return;
		}
	}
	//std::cout << "New Collision" << std::endl;
	registeredCollisions.push_back(t_collision);
}

void CollisionManager::UnregisterCollider(Collider* t_collider)
{
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
	for (std::list<Collider*>::iterator it = registeredColliders.begin(); it != registeredColliders.end(); ++it)
	{
		for (std::list<Collider*>::iterator it2 = registeredColliders.begin(); it2 != registeredColliders.end(); ++it2)
		{
			if (it != it2 && 
				(*it)->GetObjectBelongingTo() != (*it2)->GetObjectBelongingTo() && 
				(glm::distance((*it)->GetPosition() + (*it)->GetRect().GetDimensions() / 2.0f, (*it2)->GetPosition() + (*it2)->GetRect().GetDimensions() / 2.0f) < COLLISION_CHECKING_DISTANCE ||
				glm::distance((*it)->GetPosition() + (*it)->GetRect().GetDimensions() / 2.0f, (*it2)->GetPosition() + (*it2)->GetRect().GetDimensions() / 2.0f) < (*it)->GetCollisionDistance()))
			{
				(*it)->TestCollision((*it2));
				(*it2)->TestCollision((*it));
			}

			if (it2 == registeredColliders.end()) break;
		}

		if (it == registeredColliders.end()) break;
	}

	while (!registeredCollisions.empty())
	{
		registeredCollisions.back()->FirstCollider->HandleCollisions(registeredCollisions.back()->SecondCollider);
		registeredCollisions.back()->SecondCollider->HandleCollisions(registeredCollisions.back()->FirstCollider);
		registeredCollisions.pop_back();
	}
}

std::list<Collider*>* CollisionManager::GetVectorOfColliders()
{
	return &registeredColliders;
}
