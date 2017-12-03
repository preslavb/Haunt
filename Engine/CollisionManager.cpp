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
			std::cout << "Prevented duplicate collision" << std::endl;
			return;
		}
	}
	registeredCollisions.push_back(t_collision);
}

void CollisionManager::UnregisterCollider(Collider* t_collider)
{
	for (std::vector<Collider*>::iterator removeIt = registeredColliders.begin(); removeIt != registeredColliders.end(); ++removeIt)
	{
		registeredColliders.erase(removeIt);
		break;
	}
}

void CollisionManager::Update()
{
	for (std::vector<Collider*>::iterator it = registeredColliders.begin(); it != registeredColliders.end(); ++it)
	{
		for (std::vector<Collider*>::iterator it2 = registeredColliders.begin(); it2 != registeredColliders.end(); ++it2)
		{
			if (it != it2 && (*it)->GetObjectBelongingTo() != (*it2)->GetObjectBelongingTo() && glm::distance((*it)->GetPosition(), (*it2)->GetPosition()) < COLLISION_CHECKING_DISTANCE)
			{
				if (!(*it)->TestCollision((*it2)))
				{
					(*it2)->TestCollision((*it));
				}
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

std::vector<Collider*>* CollisionManager::GetVectorOfColliders()
{
	return &registeredColliders;
}
