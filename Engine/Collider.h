#pragma once
#include <glm/detail/type_vec2.hpp>
#include "Rect.h"
#include <unordered_map>

class GameObject;

enum class CollisionState
{
	None,
	Entered,
	Colliding,
	Escaped
};

[event_source(native)]
class Collider
{
private:
	Rect boundingBox;
	GameObject* belongsTo;

	std::unordered_map<Collider*, CollisionState> collisionsMap;

	glm::vec2 position;
	glm::vec2 offset;

	float collisionDistance = 0;
public:
	Collider(glm::vec2 t_position, Rect t_bounding_box, GameObject* t_belonging_to);
	~Collider();

	bool TestCollision(Collider* t_other_collider);
	void HandleCollisions(Collider* t_other_collider);

	glm::vec2 GetPosition();
	glm::vec2 GetOffset();
	Rect GetRect();
	GameObject* GetObjectBelongingTo();
	CollisionState GetCollisionState(Collider* t_other_collider);
	void SetCollisionState(Collider* t_other_collider, CollisionState t_collision_state);
	float GetCollisionDistance();
	void SetPosition(glm::vec2 t_new_position);
	void SetCollisionDistance(float t_new_distance);

	__event void OnCollision(Collider* t_other_collider);
	__event void DuringCollision(Collider* t_other_collider);
	__event void OnEscape(Collider* t_other_collider);
};

struct Collision
{
	Collision(Collider* t_first_collider, Collider* t_second_collider) : FirstCollider(t_first_collider), SecondCollider(t_second_collider)
	{
	}

	Collider* FirstCollider;
	Collider* SecondCollider;
};