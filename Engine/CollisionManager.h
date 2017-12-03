#pragma once
#include <vector>
#include "Collider.h"

static float const COLLISION_CHECKING_DISTANCE = 200.0f;

class CollisionManager
{
private:
	std::vector<Collider*>::iterator it;
	std::vector<Collider*>::iterator it2;

	static CollisionManager* instance;
	std::vector<Collider*> registeredColliders;
	std::vector<Collision*> registeredCollisions;
public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager* GetInstance();

	void RegisterCollider(Collider* t_collider);
	void RegisterCollision(Collision* t_collision);
	void UnregisterCollider(Collider* t_collider);

	void Update();
	std::vector<Collider*>* GetVectorOfColliders();
};

