#include "Character.h"
#include "Game.h"
#include "Engine/CollisionManager.h"
#include "Engine/GarbageDestroyer.h"

void Character::HookCharacterCollisionEvents()
{
	__hook(&Collider::OnCollision, &mainCollider, &Character::HandleFloorCollision);
	__hook(&Collider::OnEscape, &mainCollider, &Character::EscapeFloorCollision);
}

// Constructors, using the Dynamic constructors
Character::Character(Texture* t_texture_to_use, Rect t_custom_collider_dimensions) : Dynamic(t_texture_to_use), mainCollider(glm::vec2(0, 0), t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(50, 50)), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, Rect t_custom_collider_dimensions) : Dynamic(t_texture_to_use, t_new_position), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, Rect t_custom_collider_dimensions) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth, Rect t_custom_collider_dimensions) : Dynamic(
	t_texture_to_use, t_new_position, t_new_depth), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, const int t_new_health, Rect t_custom_collider_dimensions) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = t_new_health;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::~Character()
{
	/*for (Collider* collider : colliders)
	{
		CollisionManager::GetInstance()->UnregisterCollider(collider);
	}*/

	for (vector<GameObject*>::iterator it = Game::GetInstance()->GetGameObjects()->begin(); it != Game::GetInstance()->GetGameObjects()->end(); ++it)
	{
		if ((*it) == this)
		{
			auto gameObjects = Game::GetInstance()->GetGameObjects();
			gameObjects->erase(it);
			break;
		}
	}
}

void Character::MoveRight(float t_delta_time)
{
	this->isMovingRight = true;
	this->isMoving = true;

	if (!isMovingLeft && !isHit)
	{
		this->velocity.x = baseSpeed;

		if (this->acceleration.x < MAX_ACCELERATION)
		{
			this->acceleration.x += RUN_ACCELERATION * _METER * t_delta_time;
		}

		this->currentDirection = Direction::Right;
	}
}

void Character::MoveLeft(float t_delta_time)
{
	this->isMovingLeft = true;
	this->isMoving = true;

	if (!isMovingRight && !isHit)
	{
		this->velocity.x = -baseSpeed;

		if (this->acceleration.x > -MAX_ACCELERATION)
		{
			this->acceleration.x -= RUN_ACCELERATION * _METER * t_delta_time;
		}

		this->currentDirection = Direction::Left;
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

void Character::ForceJump(Collider* t_enemy_collider)
{
	if (t_enemy_collider->GetObjectBelongingTo()->GetType() == "Enemy")
	{
		if (!isHit)
		{
			this->grounded = false;
			this->hasJumped = true;
			this->velocity.y = JUMP_FORCE_HIT;
		}
	}
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
		if (this->acceleration.x - _FRICTION * _METER * Compare(acceleration.x, 0) * t_delta_time < 0 && Compare(acceleration.x, 0) >= 0)
		{
			acceleration.x = 0;
		}
		else if (this->acceleration.x - (_FRICTION * _METER * Compare(acceleration.x, 0) * t_delta_time) > 0 && Compare(acceleration.x, 0) < 0)
		{
			acceleration.x = 0;
		}
		// Otherwise, apply friction to their acceleration value
		else
		{
			this->acceleration.x -= _FRICTION * _METER * Compare(acceleration.x, 0) * t_delta_time;
			//this->velocity.x = acceleration.x;
		}
	}

	// If the character is not grounded, apply the force of gravity, based on the time since the last frame. If they are, set their y velocity to 0
	if (!grounded)
	{
		this->velocity.y -= _GRAVITY * _METER * t_delta_time;

		/*if (position.y + dimensions.y < 0)
		{
			Die();
		}*/
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

void Character::Ground(float t_ground_height)
{
	if (!hasJumped)
	{
		grounded = true;
		isHit = false;
		this->SetPosition(glm::vec2(this->GetPosition().x, t_ground_height));
	}
}

void Character::Unground()
{
	grounded = false;
}

void Character::Move(const glm::vec2 t_offset)
{
	// Offset the object by the specified std::vec2
	this->SetPosition(this->GetPosition() + t_offset);

	for (Collider* collider : colliders)
	{
		collider->SetPosition(position + collider->GetOffset());
	}
}

void Character::SetPosition(glm::vec2 t_new_position)
{
	position = t_new_position;

	for (Collider* collider : colliders)
	{
		collider->SetPosition(t_new_position + collider->GetOffset());
	}
}

void Character::WasHitByPlayer(Collider* t_player_collider, Collider* t_collider_hit)
{
	if (Player::GetInstance()->GetHitCollider()->GetCollisionState(&mainCollider) == CollisionState::None && t_player_collider->GetObjectBelongingTo()->GetType() == "Player")
	{
		std::cout << "Character was hit by the player, dealing 100 DMG" << std::endl;
		Player::GetInstance()->ForceJump(&mainCollider);
		Damage(100);
	}
}

void Character::HandleFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		floorsCollidingWith++;
		if (t_friendly_collider->GetPosition().y >= t_other_collider->GetPosition().y + (t_other_collider->GetDimensions().y) - 20)
		{
			velocity.y <= 0 ? Ground(t_other_collider->GetPosition().y + (t_other_collider->GetDimensions().y)) : velocity.x = 0;
		}

		else
		{
			if (t_friendly_collider->GetPosition().x <= (t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x / 2))
			{
				isMovingLeft = true;
				velocity = glm::vec2(-velocity.x, velocity.y);
				acceleration = glm::vec2(-acceleration.x, acceleration.y);
				position = glm::vec2(t_other_collider->GetPosition().x - t_friendly_collider->GetDimensions().x, position.y);
			}
			else if (t_friendly_collider->GetPosition().x >= (t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x / 2))
			{
				isMovingLeft = false;
				velocity = glm::vec2(-velocity.x, velocity.y);
				acceleration = glm::vec2(-acceleration.x, acceleration.y);
				position = glm::vec2(t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x, position.y);
			}
		}
	}
}

void Character::EscapeFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		floorsCollidingWith--;
		if (floorsCollidingWith <= 0) Unground();
	}
}

bool Character::IsHit()
{
	return isHit;
}

void Character::Damage(const int t_amount_of_damage)
{
	// Decrement the health of the character by the amount of damage passed to the function
	this->health -= t_amount_of_damage;
	this->isHit = true;

	if (health <= 0)
	{
		Die();
	}
}

void Character::Die()
{
	GarbageDestroyer<Character*>::GetInstance()->Destroy(this);
}

Collider* Character::GetMainCollider()
{
	return &mainCollider;
}
