#include "Enemy.h"
#include "Player.h"

void Enemy::HookEnemyEvents()
{
	__hook(&Collider::OnCollision, Player::GetInstance()->GetAttackCollider(), &Enemy::WasHitByPlayer);
}

Enemy::Enemy(Texture* t_texture_to_use) : Character(t_texture_to_use)
{
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position) : Character(t_texture_to_use, t_new_position)
{
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation) : Character(t_texture_to_use, t_new_position, t_new_rotation)
{
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth) : Character(t_texture_to_use, t_new_position, t_new_depth)
{
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, int t_new_health) : Character(t_texture_to_use, t_new_position, t_new_rotation, t_new_health)
{
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

void Enemy::Update(float t_delta_time)
{
	if (IsOnScreen(Camera2D::GetMainCamera()))
	{
		Enemy::MoveLeft(t_delta_time);

		Character::Update(t_delta_time);

		std::cout << position.x << " , " << position.y << std::endl;
	}
}
