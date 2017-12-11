#include "Enemy.h"
#include "Player.h"
#include "Game.h"

void Enemy::HookEnemyEvents()
{
	__hook(&Collider::OnCollision, &mainCollider, &Enemy::WasHitByPlayer);
	//__hook(&Collider::OnCollision, Player::GetInstance()->GetAttackCollider(), &Enemy::WasHitByPlayer);
}

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

void Enemy::MoveLeft(float t_delta_time)
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

void Enemy::MoveRight(float t_delta_time)
{
	this->isMovingRight = true;
	this->isMoving = true;

	if (!isMovingLeft)
	{
		this->velocity.x = baseSpeed;

		if (this->acceleration.x < MAX_ACCELERATION)
		{
			this->acceleration.x += RUN_ACCELERATION * _METER * t_delta_time;
		}
	}
}

void Enemy::Die()
{
	Game::GetInstance()->AddScore();

	Character::Die();
}

void Enemy::Update(float t_delta_time)
{
	if (IsOnScreen(Camera2D::GetMainCamera()))
	{
		isEnabled = true;
	}

	if (isEnabled)
	{
		isMovingLeft ? MoveLeft(t_delta_time) : MoveRight(t_delta_time);

		Character::Update(t_delta_time);
	}
}
