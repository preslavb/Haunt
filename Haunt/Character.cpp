#include "Character.h"
#include "Game.h"
#include "Engine/CollisionManager.h"
#include "Engine/GarbageDestroyer.h"

void Character::HookCharacterCollisionEvents()
{
	__hook(&Collider::OnCollision, &mainCollider, &Character::TestCollisionsCharacter);
}

void Character::TestCollisionsCharacter()
{
	//cout << "Collision on Character" << endl;
}

// Constructors, using the Dynamic constructors
Character::Character(Texture* t_texture_to_use) : Dynamic(t_texture_to_use), mainCollider(glm::vec2(0, 0), Rect(glm::vec2(0, 0), glm::vec2(50, 50)), this)
{
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position) : Dynamic(t_texture_to_use, t_new_position), mainCollider(t_new_position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation), mainCollider(t_new_position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth) : Dynamic(
	t_texture_to_use, t_new_position, t_new_depth), mainCollider(t_new_position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, const int t_new_health) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation), mainCollider(t_new_position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	this->health = t_new_health;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::~Character()
{
	for (Collider* collider : colliders)
	{
		CollisionManager::GetInstance()->UnregisterCollider(collider);
	}
}

void Character::MoveRight(float t_delta_time)
{
	this->isMovingRight = true;
	this->isMoving = true;

	if (!(isMovingLeft))
	{
		this->velocity.x = baseSpeed;

		if (this->acceleration.x < MAX_ACCELERATION)
		{
			this->acceleration.x += RUN_ACCELERATION * _METER * t_delta_time;
		}
	}
}

void Character::MoveLeft(float t_delta_time)
{
	this->isMovingLeft = true;
	this->isMoving = true;

	if (!(isMovingRight))
	{
		this->velocity.x = -baseSpeed;

		if (this->acceleration.x > -MAX_ACCELERATION)
		{
			this->acceleration.x -= RUN_ACCELERATION * _METER * t_delta_time;
		}
	}
}

void Character::StopMoving(float t_delta_time)
{
	this->isMoving = false;
	this->isMovingLeft = false;
	this->isMovingRight = false;
}

void Character::Jump(float t_delta_time)
{
	if (grounded)
	{
		this->grounded = false;
		this->hasJumped = true;
		this->velocity.y = JUMP_FORCE;
	}
}

void Character::ForceJump()
{
	this->grounded = false;
	this->hasJumped = true;
	this->velocity.y = JUMP_FORCE_HIT;
}

void Character::LimitJump(float t_delta_time)
{
	if (!grounded && velocity.y > JUMP_LIMIT)
	{
		velocity.y = JUMP_LIMIT;
	}
}

void Character::Update(const float t_delta_time)
{
	// If the character is not deliberately moving, apply the brakes
	if (!isMoving)
	{
		// If the character would start accelerating the opposite direction the next frame (non deliberately), stop them from doing so by setting their acceleration to 0
		if (this->acceleration.x - _FRICTION * _METER * ::Compare(acceleration.x, 0) * t_delta_time < 0 && ::Compare(acceleration.x, 0) >= 0)
		{
			acceleration.x = 0;
		}
		else if (this->acceleration.x - (_FRICTION * _METER * ::Compare(acceleration.x, 0) * t_delta_time) > 0 && ::Compare(acceleration.x, 0) < 0)
		{
			acceleration.x = 0;
		}
		// Otherwise, apply friction to their acceleration value
		else
		{
			this->acceleration.x -= _FRICTION * _METER * ::Compare(acceleration.x, 0) * t_delta_time;
			this->velocity.x = acceleration.x;
		}
	}

	// If the character has hit the ground, stop applying gravity to them
	if (this->GetPosition().y < 200 && !hasJumped)
	{
		grounded = true;
		this->SetPosition(glm::vec2(this->GetPosition().x, 200));
	}

	// If the character is not grounded, apply the force of gravity, based on the time since the last frame. If they are, set their y velocity to 0
	if (!grounded)
	{
		this->velocity.y -= _GRAVITY * _METER * t_delta_time;
	}
	else
	{
		this->velocity.y = 0;
	}

	// Move the character based on their velocity and acceleration
	this->Move((this->velocity + this->acceleration) * _METER * t_delta_time);

	// Jump can only happen in the frame that it was pressed, so disable it afterwards
	hasJumped = false;
}

void Character::Move(const glm::vec2 t_offset)
{
	// Offset the object by the specified std::vec2
	this->SetPosition(this->GetPosition() + t_offset);

	for (Collider* collider : colliders)
	{
		collider->SetPosition(position);
	}
}

void Character::WasHitByPlayer()
{
	std::cout << "Character was hit by the player, dealing 100 DMG" << std::endl;
	Damage(99);
}

void Character::Damage(const int t_amount_of_damage)
{
	// Decrement the health of the character by the amount of damage passed to the function
	this->health -= t_amount_of_damage;

	if (health <= 0)
	{
		Die();
	}
}

void Character::Die()
{
	for (std::vector<GameObject*>::iterator it = Game::GetInstance()->GetGameObjects()->begin(); it != Game::GetInstance()->GetGameObjects()->end(); ++it)
	{
		if ((*it) == this)
		{
			it = Game::GetInstance()->GetGameObjects()->erase(it);
			GarbageDestroyer<Character*>::GetInstance()->Destroy(this);
			break;
		}
	}
}
