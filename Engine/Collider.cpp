#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"
#include <iostream>


void Collider::HandleCollisions(Collider* t_other_collider)
{
	std::unordered_map<Collider*, CollisionState>::const_iterator thePair = collisionsMap.find(t_other_collider);

	if (thePair != collisionsMap.end())
	{
		switch (collisionsMap.find(t_other_collider)->second)
		{
		case CollisionState::Entered:
			__raise OnCollision();
			break;
		case CollisionState::Colliding:
			__raise DuringCollision();
			break;
		case CollisionState::Escaped:
			__raise OnEscape();
			break;
		default:
			break;
		}
	}
	else
	{
		collisionsMap[t_other_collider] = CollisionState::None;
		t_other_collider->collisionsMap[this] = CollisionState::None;
	}
}

Collider::Collider(glm::vec2 t_position, Rect t_bounding_box, GameObject* t_belonging_to) :
	position(t_position),
	boundingBox(t_bounding_box),
	belongsTo(t_belonging_to)
{
	boundingBox.SetPosition(position);
	CollisionManager::GetInstance()->RegisterCollider(this);
}

Collider::~Collider()
{
}

// Test for collision between two colliders
bool Collider::TestCollision(Collider* t_other_collider)
{
	if (collisionsMap.find(t_other_collider) != collisionsMap.end())
	{
		std::cout << belongsTo << " : " << (int)collisionsMap.find(t_other_collider)->second << std::endl;
	}
	
	// A bounding box corner is withing the bounding box of the other collider
	if ((boundingBox.BottomLeft().x <= t_other_collider->boundingBox.TopRight().x && boundingBox.BottomLeft().x >= t_other_collider->boundingBox.TopLeft().x
		&& boundingBox.BottomLeft().y >= t_other_collider->boundingBox.TopRight().y && boundingBox.BottomLeft().y <= t_other_collider->boundingBox.BottomRight().y)
		||
		(boundingBox.TopLeft().x <= t_other_collider->boundingBox.BottomRight().x && boundingBox.TopLeft().x >= t_other_collider->boundingBox.BottomLeft().x
		&& boundingBox.TopLeft().y <= t_other_collider->boundingBox.BottomRight().y && boundingBox.TopLeft().y >= t_other_collider->boundingBox.TopRight().y)
		||
		(boundingBox.TopRight().x >= t_other_collider->boundingBox.BottomLeft().x && boundingBox.TopRight().x <= t_other_collider->boundingBox.BottomRight().x
		&& boundingBox.TopRight().y <= t_other_collider->boundingBox.BottomLeft().y && boundingBox.TopRight().y >= t_other_collider->boundingBox.TopLeft().y)
		||
		(boundingBox.BottomRight().x >= t_other_collider->boundingBox.TopLeft().x && boundingBox.BottomRight().x <= t_other_collider->boundingBox.TopRight().x
		&& boundingBox.BottomRight().y >= t_other_collider->boundingBox.TopLeft().y && boundingBox.BottomRight().y <= t_other_collider->boundingBox.BottomLeft().y))
	{
		CollisionManager::GetInstance()->RegisterCollision(new Collision(this, t_other_collider));

		switch (collisionsMap[t_other_collider])
		{
		case CollisionState::None:
			collisionsMap[t_other_collider] = CollisionState::Entered;
			return true;
		case CollisionState::Entered:
			collisionsMap[t_other_collider] = CollisionState::Colliding;
			return true;
		case CollisionState::Colliding:
			collisionsMap[t_other_collider] = CollisionState::Colliding;
			return true;
		default:
			return true;
		}
	}

	if (collisionsMap[t_other_collider] == CollisionState::Colliding)
	{
		collisionsMap[t_other_collider] = CollisionState::Escaped;
		return true;
	}

	collisionsMap[t_other_collider] = CollisionState::None;
	return false;
}

glm::vec2 Collider::GetPosition()
{
	return position;
}

Rect Collider::GetRect()
{
	return boundingBox;
}

GameObject* Collider::GetObjectBelongingTo()
{
	return belongsTo;
}

void Collider::SetPosition(glm::vec2 t_new_position)
{
	position = t_new_position;

	boundingBox.SetPosition(t_new_position);
}
