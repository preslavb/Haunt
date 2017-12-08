#include "Player.h"
#include "Engine/Camera2D.h"
#include "Game.h"
#include "Engine/CollisionManager.h"

Player* Player::instance = nullptr;

Player::Player(Texture* t_texture_to_use) : Character(t_texture_to_use), attackCollider(position + glm::vec2(-100, 0), Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight()/2)), this)
{
	if (Player::instance != nullptr)
	{
		delete Player::instance;
	}

	type = "Player";

	mainCollider.SetPosition(glm::vec2(position.x, position.y + t_texture_to_use->GetTextureHeight()));
	mainCollider.SetRect(Rect(glm::vec2(0, 0.5), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)));

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

	type = "Player";
	if (&mainCollider != nullptr)
	{
		CollisionManager::GetInstance()->UnregisterCollider(&mainCollider);
	}

	mainCollider = Collider(position + glm::vec2(0, dimensions.y / 2), Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this);

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

	type = "Player";

	mainCollider.SetPosition(glm::vec2(position.x, position.y + t_texture_to_use->GetTextureWidth() / 2));
	mainCollider.SetRect(Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)));

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

	type = "Player";

	mainCollider.SetPosition(glm::vec2(position.x, position.y + t_texture_to_use->GetTextureWidth() / 2));
	mainCollider.SetRect(Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)));

	Player::instance = this;
	colliders.push_back(&attackCollider);
	HookInputEvent();
	HookCollisionEvents();
}

Collider* Player::GetAttackCollider()
{
	return &attackCollider;
}

Collider* Player::GetHitCollider()
{
	return &mainCollider;
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
	__hook(&Collider::OnCollision, &mainCollider, &Player::WasHitByEnemy);
	__hook(&Collider::OnCollision, &attackCollider, &Player::HasHitEnemy);
	__hook(&Collider::OnCollision, &attackCollider, &Player::HandleFloorCollision);
	__hook(&Collider::DuringCollision, &attackCollider, &Player::HandleFloorCollision);
	//__hook(&Collider::DuringCollision, &attackCollider, &Player::HandleFloorCollision);
	__hook(&Collider::OnEscape, &mainCollider, &Player::EscapeFloorCollision);
	__hook(&Collider::OnEscape, &attackCollider, &Player::EscapeFloorCollision);
	__hook(&Collider::OnCollision, &attackCollider, &Player::WasHitByEnemy);
}

void Player::WasHitByEnemy(Collider* t_enemy_collider)
{
	if (!isHit && t_enemy_collider->GetObjectBelongingTo()->GetType() == "Enemy")
	{
		SetVelocity(glm::vec2((GetPosition().x - t_enemy_collider->GetObjectBelongingTo()->GetPosition().x)*1.2, 50));
		Damage(20);
		isHit = true;
	}
}

void Player::HasHitEnemy(Collider* t_enemy_collider)
{
	if (t_enemy_collider->GetObjectBelongingTo()->GetType() == "Enemy")
	{
		ForceJump(t_enemy_collider);
	}
}

void Player::HandleFloorCollision(Collider* t_other_collider)
{
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		if (position.y >= t_other_collider->GetObjectBelongingTo()->GetPosition().y + (t_other_collider->GetObjectBelongingTo()->GetDimensions().y) - 20)
		{
			velocity.y <= 0 ? Ground(t_other_collider->GetObjectBelongingTo()->GetPosition().y + (t_other_collider->GetObjectBelongingTo()->GetDimensions().y)) : velocity.x = 0;
		}

		else if (position.y <= t_other_collider->GetObjectBelongingTo()->GetPosition().y + 200)
		{
			velocity.y = -30;
		}

		else
		{
			if (position.x <= (t_other_collider->GetObjectBelongingTo()->GetPosition().x + t_other_collider->GetObjectBelongingTo()->GetDimensions().x / 2))
			{
				velocity.x > 0 ? position = glm::vec2(t_other_collider->GetPosition().x - dimensions.x, position.y) : position -= glm::vec2(0.1f, 0);
				velocity = glm::vec2(0, velocity.y);
				acceleration = glm::vec2(0, acceleration.y);
			}
			
			if (position.x >= (t_other_collider->GetObjectBelongingTo()->GetPosition().x + t_other_collider->GetObjectBelongingTo()->GetDimensions().x / 2))
			{
				position = glm::vec2(t_other_collider->GetPosition().x + t_other_collider->GetObjectBelongingTo()->GetDimensions().x, position.y);
				velocity = glm::vec2(0, velocity.y);
				acceleration = glm::vec2(0, acceleration.y);
			}
		}
	}
}

void Player::EscapeFloorCollision(Collider* t_other_collider)
{
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		Unground();
	}
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
	for (Collider* collider : colliders)
	{
		CollisionManager::GetInstance()->UnregisterCollider(collider);
	}
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