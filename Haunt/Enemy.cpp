#include "Enemy.h"
#include "Player.h"

void Enemy::HookEnemyEvents()
{
	__hook(&Collider::OnCollision, &mainCollider, &Enemy::WasHitByPlayer);
	//__hook(&Collider::OnCollision, Player::GetInstance()->GetAttackCollider(), &Enemy::WasHitByPlayer);
}

Enemy::Enemy(Texture* t_texture_to_use) : Character(t_texture_to_use)
{
	type = "Enemy";
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position) : Character(t_texture_to_use, t_new_position)
{
	type = "Enemy";
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation) : Character(t_texture_to_use, t_new_position, t_new_rotation)
{
	type = "Enemy";
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth) : Character(t_texture_to_use, t_new_position, t_new_depth)
{
	type = "Enemy";
	HookEnemyEvents();
}

Enemy::Enemy(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, int t_new_health) : Character(t_texture_to_use, t_new_position, t_new_rotation, t_new_health)
{
	type = "Enemy";
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

void Enemy::Update(float t_delta_time)
{
	cout << (int)GetMainCollider()->GetCollisionState(Player::GetInstance()->GetAttackCollider()) << endl;

	if (IsOnScreen(Camera2D::GetMainCamera()))
	{
		//isMovingLeft ? MoveLeft(t_delta_time) : MoveRight(t_delta_time);

		Character::Update(t_delta_time);
	}
}
