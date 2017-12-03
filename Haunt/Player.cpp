#include "Player.h"
#include "Engine/Camera2D.h"
#include "Game.h"

Player* Player::instance = nullptr;

Player::Player(Texture* t_texture_to_use) : Character(t_texture_to_use), attackCollider(position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight()/2)), this)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
	colliders.push_back(&attackCollider);
	HookInputEvent();
	HookCollisionEvents();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position) : Character(t_texture_to_use, t_new_position), attackCollider(position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
	colliders.push_back(&attackCollider);
	HookInputEvent();
	HookCollisionEvents();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation) : Character(
	t_texture_to_use, t_new_position, t_new_rotation), attackCollider(position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
	colliders.push_back(&attackCollider);
	HookInputEvent();
	HookCollisionEvents();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth) : Character(
	t_texture_to_use, t_new_position, t_new_depth), attackCollider(position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	Player::instance = this;
	colliders.push_back(&attackCollider);
	HookInputEvent();
	HookCollisionEvents();
}

Collider* Player::GetAttackCollider()
{
	return &attackCollider;
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

void Player::HookCollisionEvents()
{
	//__hook(&Collider::OnCollision, &mainCollider, &Player::Damage);
	__hook(&Collider::OnCollision, &attackCollider, &Player::ForceJump);
}

void Player::Update(const float t_delta_time)
{
	// Stop moving when no movements controls are pressed for the direction (does not include acceleration)
	if ((InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::Released || InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::None) 
		&& (InputHandler::GetKeyState(SDLK_LEFT) == KeyState::Released || InputHandler::GetKeyState(SDLK_LEFT) == KeyState::None))
	{
		this->velocity.x = 0;
	}

	if (abs(instance->GetPosition().x - Game::GetInstance()->MainCamera.GetPosition().x) > 50)
	{
		Game::GetInstance()->MainCamera.SetPosition(glm::vec2(Player::GetInstance()->GetPosition().x + (50 * Compare(Game::GetInstance()->MainCamera.GetPosition().x, Player::GetInstance()->GetPosition().x)), Game::GetInstance()->MainCamera.GetPosition().y));
	}

	/*if (abs(instance->GetPosition().y - Game::GetInstance()->MainCamera.GetPosition().y) > 100)
	{
		Game::GetInstance()->MainCamera.SetPosition(glm::vec2(Game::GetInstance()->MainCamera.GetPosition().x, 100 + Player::GetInstance()->GetPosition().y + (100 * Compare(Game::GetInstance()->MainCamera.GetPosition().y, Player::GetInstance()->GetPosition().y))));
	}*/

	Character::Update(t_delta_time);
}

Player::~Player()
{
}

Player* Player::GetInstance()
{
	if (!instance)
	{
		instance = new Player(TextureManager::GetInstance()->GetTexture("grass"), glm::vec2(500, 300));
	}
	return instance;
}

Player* Player::GetInstance(Texture* t_texture_to_use)
{
	if (!instance)
	{
		instance = new Player(t_texture_to_use, glm::vec2(500, 300));
	}
	return instance;
}

Player* Player::GetInstance(Texture* t_texture_to_use, glm::vec2 t_new_position)
{
	if (!instance)
	{
		instance = new Player(t_texture_to_use, t_new_position);
	}
	return instance;
}

