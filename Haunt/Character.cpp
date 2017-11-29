#include "Character.h"
#include "Game.h"

// Constructors, using the Dynamic constructors
Character::Character(Texture* t_texture_to_use) : Dynamic(t_texture_to_use)
{
	this->health = 100;
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position) : Dynamic(t_texture_to_use, t_new_position)
{
	this->health = 100;
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation)
{
	this->health = 100;
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth) : Dynamic(
	t_texture_to_use, t_new_position, t_new_depth)
{
	this->health = 100;
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, const int t_new_health) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation)
{
	this->health = t_new_health;
}

Character::~Character()
{
}

void Character::MoveRight()
{
	this->isMovingRight = true;
	this->isMoving = true;

	if (!(isMovingLeft))
	{
		this->velocity.x = baseSpeed;

		if (this->acceleration.x < MAX_ACCELERATION)
		{
			this->acceleration.x += RUN_ACCELERATION * _METER * Game::GetInstance()->GetElapsedSeconds();
		}
	}
}

void Character::MoveLeft()
{
	this->isMovingLeft = true;
	this->isMoving = true;

	if (!(isMovingRight))
	{
		this->velocity.x = -baseSpeed;

		if (this->acceleration.x > -MAX_ACCELERATION)
		{
			this->acceleration.x -= RUN_ACCELERATION * _METER * Game::GetInstance()->GetElapsedSeconds();
		}
	}
}

void Character::StopMoving()
{
	this->isMoving = false;
	this->isMovingLeft = false;
	this->isMovingRight = false;
}

void Character::Jump()
{
	if (grounded)
	{
		this->grounded = false;
		this->hasJumped = true;
		this->velocity.y = JUMP_FORCE;
	}
}

void Character::LimitJump()
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

void Character::Damage(const int t_amount_of_damage)
{
	// Decrement the health of the character by the amount of damage passed to the function
	this->health -= t_amount_of_damage;
}
