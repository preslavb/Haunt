#include "Enemy.h"
#include "Player.h"
#include "Game.h"

void Enemy::HookEnemyEvents()
{
	__hook(&Collider::OnCollision, &mainCollider, &Enemy::WasHitByPlayer);
}

// Constructors
Enemy::Enemy(Texture* t_texture_to_use, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_custom_collider_dimensions)
{
	type = "Enemy";
	isMovingLeft = true;
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_new_position, t_custom_collider_dimensions)
{
	type = "Enemy";
	isMovingLeft = true;
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_new_position, t_new_rotation, t_custom_collider_dimensions)
{
	type = "Enemy";
	isMovingLeft = true;
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_new_position, t_new_depth, t_custom_collider_dimensions)
{
	type = "Enemy";
	isMovingLeft = true;
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, int t_new_health, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_new_position, t_new_rotation, t_new_health, t_custom_collider_dimensions)
{
	type = "Enemy";
	isMovingLeft = true;
	HookEnemyEvents();
}

// Same as the normal movement functions for a character but doesn't require the isHit check
void Enemy::MoveLeft(float t_delta_time)
{
	this->isMovingLeft = true;
	this->isMoving = true;

	if (!(isMovingRight))
	{
		currentDirection = Direction::Left;

		this->velocity.x = -baseSpeed;

		if (this->acceleration.x > -MAX_ACCELERATION)
		{
			this->acceleration.x -= RUN_ACCELERATION * _METER * t_delta_time;
		}
	}
}

// Same as the normal movement functions for a character but doesn't require the isHit check
void Enemy::MoveRight(float t_delta_time)
{
	this->isMovingRight = true;
	this->isMoving = true;

	if (!isMovingLeft)
	{
		currentDirection = Direction::Right;

		this->velocity.x = baseSpeed;

		if (this->acceleration.x < MAX_ACCELERATION)
		{
			this->acceleration.x += RUN_ACCELERATION * _METER * t_delta_time;
		}
	}
}

void Enemy::Die()
{
	// When an enemy dies, add 100 score to the player
	Game::GetInstance()->AddScore();

	// Handle the rest of the death with the character implementation
	Character::Die();
}

void Enemy::Update(float t_delta_time)
{
	// If the enemy is on screen, enable their movement
	if (IsOnScreen(Camera2D::GetMainCamera()))
	{
		isEnabled = true;
	}

	// If the enemy is enabled, move in the available direction, then update it as normal with the character implementation
	if (isEnabled)
	{
		isMovingLeft ? MoveLeft(t_delta_time) : MoveRight(t_delta_time);

		Character::Update(t_delta_time);
	}
}
