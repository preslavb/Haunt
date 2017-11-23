#include "Player.h"
#include "GameConstants.h"

Player::Player(GLuint* t_texture_to_use) : Character(t_texture_to_use)
{
	HookInputEvent();
}

Player::Player(GLuint* t_texture_to_use, const Vector2D t_new_position) : Character(t_texture_to_use, t_new_position)
{
	HookInputEvent();
}

Player::Player(GLuint* t_texture_to_use, const Vector2D t_new_position, const float t_new_rotation) : Character(
	t_texture_to_use, t_new_position, t_new_rotation)
{
	HookInputEvent();
}

void Player::HookInputEvent()
{
	__hook(&KeyState::WhenKeyHeld, InputHandler::GetInstance()->GetKeyStateClass(SDLK_RIGHT), &Player::MoveRight);
	__hook(&KeyState::WhenKeyHeld, InputHandler::GetInstance()->GetKeyStateClass(SDLK_LEFT), &Player::MoveLeft);
	__hook(&KeyState::OnKeyReleased, InputHandler::GetInstance()->GetKeyStateClass(SDLK_LEFT), &Player::StopMoving);
	__hook(&KeyState::OnKeyReleased, InputHandler::GetInstance()->GetKeyStateClass(SDLK_RIGHT), &Player::StopMoving);
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_UP), &Player::Jump);
	__hook(&KeyState::OnKeyReleased, InputHandler::GetInstance()->GetKeyStateClass(SDLK_UP), &Player::LimitJump);
}


void Player::Update(const float t_delta_time)
{
	// Movement controls Handling
	/*if (InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::Held && InputHandler::GetKeyState(SDLK_LEFT) != KeyState::Held)
	{
		this->velocity.X = baseSpeed;
		if (this->acceleration.X < MAX_ACCELERATION)
		{
			this->acceleration.X += RUN_ACCELERATION * _METER * t_delta_time;
		}

		this->isMoving = true;
	}

	else if (InputHandler::GetKeyState(SDLK_LEFT) == KeyState::Held && InputHandler::GetKeyState(SDLK_RIGHT) != KeyState::Held)
	{
		this->velocity.X = -baseSpeed;

		if (this->acceleration.X > -MAX_ACCELERATION)
		{
			this->acceleration.X -= RUN_ACCELERATION * _METER * t_delta_time;
		}

		this->isMoving = true;
	}*/

	//if (InputHandler::GetKeyState(SDLK_UP) == KeyState::Pressed && grounded)
	//{
	//	this->grounded = false;
	//	this->hasJumped = true;
	//	this->velocity.Y = -JUMP_FORCE;
	//}

	/*if (!grounded && velocity.Y < -JUMP_LIMIT && InputHandler::GetKeyState(SDLK_UP) == KeyState::Released)
	{
		velocity.Y = -JUMP_LIMIT;
	}*/

	// Stop moving when no movements controls are pressed for the direction (does not include acceleration)
	if ((InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::Released || InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::None) 
		&& (InputHandler::GetKeyState(SDLK_LEFT) == KeyState::Released || InputHandler::GetKeyState(SDLK_LEFT) == KeyState::None))
	{
		this->velocity.X = 0;
	}

	Character::Update(t_delta_time);
}

Player::~Player()
{
}
