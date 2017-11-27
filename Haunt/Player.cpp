#include "Player.h"
#include "Engine/Camera2D.h"

Player* Player::instance = nullptr;

Player::Player(Texture* t_texture_to_use) : Character(t_texture_to_use)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
	HookInputEvent();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position) : Character(t_texture_to_use, t_new_position)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
	HookInputEvent();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation) : Character(
	t_texture_to_use, t_new_position, t_new_rotation)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
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

Player* Player::GetInstance()
{
	return Player::instance;
}


void Player::Update(const float t_delta_time)
{
	// Stop moving when no movements controls are pressed for the direction (does not include acceleration)
	if ((InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::Released || InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::None) 
		&& (InputHandler::GetKeyState(SDLK_LEFT) == KeyState::Released || InputHandler::GetKeyState(SDLK_LEFT) == KeyState::None))
	{
		this->velocity.x = 0;
	}

	Character::Update(t_delta_time);
}

Player::~Player()
{
}
