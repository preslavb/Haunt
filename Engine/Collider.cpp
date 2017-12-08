#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <iostream>

void Collider::HandleCollisions(Collider* t_other_collider)
{
	std::unordered_map<Collider*, CollisionState>::const_iterator thePair = collisionsMap.find(t_other_collider);

	if (thePair != collisionsMap.end())
	{
		switch (collisionsMap.find(t_other_collider)->second)
		{
		case CollisionState::Entered:
			std::cout << "Entered" << std::endl;
			__raise OnCollision(t_other_collider);
			break;
		case CollisionState::Colliding:
			//std::cout << "Colliding" << std::endl;
			__raise DuringCollision(t_other_collider);
			break;
		case CollisionState::Escaped:
			std::cout << "Escaped" << std::endl;
			__raise OnEscape(t_other_collider);
			break;
		default:
			break;
		}
	}
	else
	{
		collisionsMap[t_other_collider] = CollisionState::None;
		//t_other_collider->collisionsMap[this] = CollisionState::None;
	}
}

Collider::Collider(glm::vec2 t_position, Rect t_bounding_box, GameObject* t_belonging_to) :
	position(t_position),
	offset(position - t_belonging_to->GetPosition()),
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
bool Collider::TestCollision(Collider* t_other_collider, bool t_already_checked)
{
	// A bounding box corner is withing the bounding box of the other collider OR a bounding box corner of the other collider is inside this bounding box 
	if (t_already_checked ||
		(((boundingBox.BottomLeft().x <= t_other_collider->boundingBox.TopRight().x && boundingBox.BottomLeft().x >= t_other_collider->boundingBox.TopLeft().x
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
		
		||
		((t_other_collider->boundingBox.BottomLeft().x <= boundingBox.TopRight().x && t_other_collider->boundingBox.BottomLeft().x >= boundingBox.TopLeft().x
		&& t_other_collider->boundingBox.BottomLeft().y >= boundingBox.TopRight().y && t_other_collider->boundingBox.BottomLeft().y <= boundingBox.BottomRight().y)
		||
		(t_other_collider->boundingBox.TopLeft().x <= boundingBox.BottomRight().x && t_other_collider->boundingBox.TopLeft().x >= boundingBox.BottomLeft().x
		&& t_other_collider->boundingBox.TopLeft().y <= boundingBox.BottomRight().y && t_other_collider->boundingBox.TopLeft().y >= boundingBox.TopRight().y)
		||
		(t_other_collider->boundingBox.TopRight().x >= boundingBox.BottomLeft().x && t_other_collider->boundingBox.TopRight().x <= boundingBox.BottomRight().x
		&& t_other_collider->boundingBox.TopRight().y <= boundingBox.BottomLeft().y && t_other_collider->boundingBox.TopRight().y >= boundingBox.TopLeft().y)
		||
		(t_other_collider->boundingBox.BottomRight().x >= boundingBox.TopLeft().x && t_other_collider->boundingBox.BottomRight().x <= boundingBox.TopRight().x
		&& t_other_collider->boundingBox.BottomRight().y >= boundingBox.TopLeft().y && t_other_collider->boundingBox.BottomRight().y <= boundingBox.BottomLeft().y))))
	{
		Collision* collision = CollisionManager::GetInstance()->CheckCollision(this, t_other_collider);

		if (collision != nullptr)
		{
			collisionsMap[t_other_collider] = collision->State;
			return true;
		}

		switch (collisionsMap[t_other_collider])
		{
		case CollisionState::None:
			collisionsMap[t_other_collider] = CollisionState::Entered;
			break;
		case CollisionState::Entered:
			collisionsMap[t_other_collider] = CollisionState::Colliding;
			break;
		case CollisionState::Colliding:
			collisionsMap[t_other_collider] = CollisionState::Colliding;
			break;
		default:
			break;
		}

		if (collisionsMap[t_other_collider] != CollisionState::None)
		{
			CollisionManager::GetInstance()->RegisterCollision(new Collision(this, t_other_collider, collisionsMap[t_other_collider]));
			return true;
		}
	}
	Collision* collision = CollisionManager::GetInstance()->CheckCollision(this, t_other_collider);

	if ((collisionsMap[t_other_collider] == CollisionState::Colliding || collisionsMap[t_other_collider] == CollisionState::Entered) &&
		collision == nullptr)
	{
		CollisionManager::GetInstance()->RegisterCollision(new Collision(this, t_other_collider, CollisionState::Escaped));
		collisionsMap[t_other_collider] = CollisionState::Escaped;
		return true;
	}
	
	if (collision != nullptr)
	{
		collisionsMap[t_other_collider] = collision->State;
	}


	collisionsMap[t_other_collider] = CollisionState::None;
	return false;
}

glm::vec2 Collider::GetPosition()
{
	return position;
}

glm::vec2 Collider::GetOffset()
{
	return offset;
}

Rect Collider::GetRect()
{
	return boundingBox;
}

void Collider::SetRect(Rect t_new_rect)
{
	boundingBox = t_new_rect;
}

GameObject* Collider::GetObjectBelongingTo()
{
	return belongsTo;
}

CollisionState Collider::GetCollisionState(Collider* t_other_collider)
{
	if (collisionsMap.find(t_other_collider) != collisionsMap.end())
	{
		return collisionsMap.find(t_other_collider)->second;
	}

	return CollisionState::None;
}

void Collider::SetCollisionState(Collider* t_other_collider, CollisionState t_collision_state)
{
	collisionsMap[t_other_collider] = t_collision_state;
}

float Collider::GetCollisionDistance()
{
	return collisionDistance;
}

void Collider::SetPosition(glm::vec2 t_new_position)
{
	position = t_new_position;

	boundingBox.SetPosition(t_new_position);
}

void Collider::SetCollisionDistance(float t_new_distance)
{
	collisionDistance = t_new_distance;
}
