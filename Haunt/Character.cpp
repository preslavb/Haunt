#include "Character.h"
#include "Game.h"

// Constructors, using the Dynamic constructors
Character::Character(GLuint* t_texture_to_use) : Dynamic(t_texture_to_use)
{
	this->health = 100;
}

Character::Character(GLuint* t_texture_to_use, const Vector2D t_new_position) : Dynamic(t_texture_to_use, t_new_position)
{
	this->health = 100;
}

Character::Character(GLuint* t_texture_to_use, const Vector2D t_new_position, const float t_new_rotation) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation)
{
	this->health = 100;
}

Character::Character(GLuint* t_texture_to_use, const Vector2D t_new_position, const float t_new_rotation, const int t_new_health) : Dynamic(
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
		this->velocity.X = baseSpeed;

		if (this->acceleration.X < MAX_ACCELERATION)
		{
			this->acceleration.X += RUN_ACCELERATION * _METER * Game::GetInstance()->GetElapsedSeconds();
		}
	}
}

void Character::MoveLeft()
{
	this->isMovingLeft = true;
	this->isMoving = true;

	if (!(isMovingRight))
	{
		this->velocity.X = -baseSpeed;

		if (this->acceleration.X > -MAX_ACCELERATION)
		{
			this->acceleration.X -= RUN_ACCELERATION * _METER * Game::GetInstance()->GetElapsedSeconds();
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
		this->velocity.Y = -JUMP_FORCE;
	}
}

void Character::LimitJump()
{
	if (!grounded && velocity.Y < -JUMP_LIMIT)
	{
		velocity.Y = -JUMP_LIMIT;
	}
}

void Character::Update(const float t_delta_time)
{
	// If the character is not deliberately moving, apply the brakes
	if (!isMoving)
	{
		// If the character would start accelerating the opposite direction the next frame (non deliberately), stop them from doing so by setting their acceleration to 0
		if (this->acceleration.X - _FRICTION * _METER * Vector2D::CompareX(acceleration, Vector2D(0, 0)) * t_delta_time < 0 && Vector2D::CompareX(acceleration, Vector2D(0, 0)) >= 0)
		{
			acceleration.X = 0;
		}
		else if (this->acceleration.X - (_FRICTION * _METER * Vector2D::CompareX(acceleration, Vector2D(0, 0)) * t_delta_time) > 0 && Vector2D::CompareX(acceleration, Vector2D(0, 0)) < 0)
		{
			acceleration.X = 0;
		}
		// Otherwise, apply friction to their acceleration value
		else
		{
			this->acceleration.X -= _FRICTION * _METER * Vector2D::CompareX(acceleration, Vector2D(0, 0)) * t_delta_time;
			this->velocity.X = acceleration.X;
		}
	}

	// If the character has hit the ground, stop applying gravity to them
	if (this->GetPosition().Y > 600 && !hasJumped)
	{
		grounded = true;
		this->SetPosition(Vector2D(this->GetPosition().X, 600));
	}

	// If the character is not grounded, apply the force of gravity, based on the time since the last frame. If they are, set their y velocity to 0
	if (!grounded)
	{
		this->velocity.Y += _GRAVITY * _METER * t_delta_time;
	}
	else
	{
		this->velocity.Y = 0;
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
