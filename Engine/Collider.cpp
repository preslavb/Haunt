#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <iostream>

void Collider::HandleCollisions(Collider* t_other_collider, Collision* t_collision)
{
	// Fire the appropriate event for the state of the collision 
	switch (t_collision->State)
	{
	case CollisionState::Entered:
		__raise OnCollision(t_other_collider, this);
		break;
	case CollisionState::Colliding:
		__raise DuringCollision(t_other_collider, this);
		break;
	case CollisionState::Escaped:
		__raise OnEscape(t_other_collider, this);
		break;
	default:
		break;
	}
}

// Collider constructor
Collider::Collider(glm::vec2 t_position, Rect t_bounding_box, GameObject* t_belonging_to) :
	position(t_position),
	offset(position - t_belonging_to->GetPosition()),
	boundingBox(t_bounding_box),
	belongsTo(t_belonging_to)
{
	boundingBox.SetPosition(position);

	// Register the collider in the collisions manager as soon as it is created
	CollisionManager::GetInstance()->RegisterCollider(this);
}

Collider::~Collider()
{
	// When the collider is being destroyed, unregister it from the collision manager
	CollisionManager::GetInstance()->UnregisterCollider(this);
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
		// Check if the collision wasn't already registered
		Collision* collision = CollisionManager::GetInstance()->CheckCollision(this, t_other_collider);

		// If it was, just set the state of this collider's collision map with the other collider to the returned state, then stop execution
		if (collision != nullptr)
		{
			collisionsMap[t_other_collider] = collision->State;
			return true;
		}

		// A collision wasn't found, so check the state of the collision and register it
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

		// If the new collision state isnt none, register the collision in the collisions manager
		if (collisionsMap[t_other_collider] != CollisionState::None)
		{
			CollisionManager::GetInstance()->RegisterCollision(new Collision(this, t_other_collider, collisionsMap[t_other_collider]));
			return true;
		}
	}

	// There was no overlap detected, so check for a collision registered by the other collider
	Collision* collision = CollisionManager::GetInstance()->CheckCollision(this, t_other_collider);

	// If a collision wasn't detected by the other collider, but the current state is one of active collision, that means that the colliders escaped this frame, so register the escaped collision
	if ((collisionsMap[t_other_collider] == CollisionState::Colliding || collisionsMap[t_other_collider] == CollisionState::Entered) &&
		collision == nullptr)
	{
		CollisionManager::GetInstance()->RegisterCollision(new Collision(this, t_other_collider, CollisionState::Escaped));
		collisionsMap[t_other_collider] = CollisionState::Escaped;
		return true;
	}
	
	// Otherwise if there was a collision registered by the other collider, then set the current collider's state to that
	if (collision != nullptr)
	{
		collisionsMap[t_other_collider] = collision->State;
		return true;
	}

	// There was no collision registered between the two colliders so just set the state to none and return a false
	collisionsMap[t_other_collider] = CollisionState::None;
	return false;
}

// Accessors
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

glm::vec2 Collider::GetDimensions()
{
	return glm::vec2(boundingBox.GetDimensions());
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
