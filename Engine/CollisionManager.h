#pragma once
#include <vector>
#include "Collider.h"

static float const COLLISION_CHECKING_DISTANCE = 200.0f;

class CollisionManager
{
private:
	std::list<Collider*>::iterator it;
	std::list<Collider*>::iterator it2;

	static CollisionManager* instance;
	std::list<Collider*> registeredColliders;
	std::list<Collision*> registeredCollisions;
public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager* GetInstance();

	void RegisterCollider(Collider* t_collider);
	bool RegisterCollision(Collision* t_collision);
	Collision* CheckCollision(Collider* t_first_collider, Collider* t_second_collider);
	void UnregisterCollider(Collider* t_collider);

	void Update();
	std::list<Collider*>* GetVectorOfColliders();
};

