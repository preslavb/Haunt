#include "Player.h"
#include "Engine/Camera2D.h"
#include "Game.h"
#include "Engine/CollisionManager.h"
#include "Engine/GarbageDestroyer.h"

// Initialize the player instance to a null pointer
Player* Player::instance = nullptr;

Player::Player(Texture* t_texture_to_use, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_custom_collider_dimensions), attackCollider(position + glm::vec2(-100, 0), Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight()/2)), this)
{
	// If an instance of a player has already been created, delete it and instantiate a new one
	if (Player::instance != nullptr)
	{
		GarbageDestroyer<Character*>::GetInstance()->Destroy(instance);
	}

	type = "Player";

	// Set the main collider to a new collider with the custom dimensions specified at the top half of the player
	mainCollider = Collider(position + glm::vec2(0, dimensions.y / 2), Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this);

	// Reset the player instance
	Player::instance = this;

	// Store the attack collider (initialized in the initialization list) in the colliders
	colliders.push_back(&attackCollider);

	// Hook up the event handlers
	HookInputEvent();
	HookCollisionEvents();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position, Rect t_custom_collider_dimensions) : Character(t_texture_to_use, t_new_position, t_custom_collider_dimensions), attackCollider(position + glm::vec2(0 + t_custom_collider_dimensions.GetPosition().x, t_custom_collider_dimensions.GetPosition().y), t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this)
{
	// If an instance of a player has already been created, delete it and instantiate a new one
	if (Player::instance != nullptr)
	{
		GarbageDestroyer<Character*>::GetInstance()->Destroy(instance);
	}

	type = "Player";

	// Set the main collider to a new collider with the custom dimensions specified at the top half of the player
	mainCollider = Collider(position + glm::vec2(0 + t_custom_collider_dimensions.GetPosition().x, (dimensions.y / 2) + t_custom_collider_dimensions.GetPosition().y), t_custom_collider_dimensions.IsValid() ? Rect(glm::vec2(0,0), glm::vec2(t_custom_collider_dimensions.GetDimensions())) : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this);

	// Reset the player instance
	Player::instance = this;

	// Store the attack collider (initialized in the initialization list) in the colliders
	colliders.push_back(&attackCollider);

	// Hook up the event handlers
	HookInputEvent();
	HookCollisionEvents();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, Rect t_custom_collider_dimensions) : Character(
	t_texture_to_use, t_new_position, t_new_rotation, t_custom_collider_dimensions), attackCollider(position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this)
{
	// If an instance of a player has already been created, delete it and instantiate a new one
	if (Player::instance != nullptr)
	{
		GarbageDestroyer<Character*>::GetInstance()->Destroy(instance);
	}

	type = "Player";

	// Set the main collider to a new collider with the custom dimensions specified at the top half of the player
	mainCollider = Collider(position + glm::vec2(0, dimensions.y / 2), Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this);

	// Reset the player instance
	Player::instance = this;

	// Store the attack collider (initialized in the initialization list) in the colliders
	colliders.push_back(&attackCollider);

	// Hook up the event handlers
	HookInputEvent();
	HookCollisionEvents();
}

Player::Player(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth, Rect t_custom_collider_dimensions) : Character(
	t_texture_to_use, t_new_position, t_new_depth, t_custom_collider_dimensions), attackCollider(position, Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this)
{
	// If an instance of a player has already been created, delete it and instantiate a new one
	if (Player::instance != nullptr)
	{
		GarbageDestroyer<Character*>::GetInstance()->Destroy(instance);
	}

	type = "Player";

	// Set the main collider to a new collider with the custom dimensions specified at the top half of the player
	mainCollider = Collider(position + glm::vec2(0, dimensions.y / 2), Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight() / 2)), this);

	// Reset the player instance
	Player::instance = this;

	// Store the attack collider (initialized in the initialization list) in the colliders
	colliders.push_back(&attackCollider);

	// Hook up the event handlers
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

// Hook up input events with their handlers
void Player::HookInputEvent()
{
	__hook(&KeyState::WhenKeyHeld, InputHandler::GetInstance()->GetKeyStateClass(SDLK_RIGHT), &Player::MoveRight);
	__hook(&KeyState::WhenKeyHeld, InputHandler::GetInstance()->GetKeyStateClass(SDLK_LEFT), &Player::MoveLeft);
	__hook(&KeyState::OnKeyReleased, InputHandler::GetInstance()->GetKeyStateClass(SDLK_LEFT), &Player::StopMoving);
	__hook(&KeyState::OnKeyReleased, InputHandler::GetInstance()->GetKeyStateClass(SDLK_RIGHT), &Player::StopMoving);
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_UP), &Player::Jump);
	__hook(&KeyState::OnKeyReleased, InputHandler::GetInstance()->GetKeyStateClass(SDLK_UP), &Player::LimitJump);
}

// Hook up collision events with their handlers
void Player::HookCollisionEvents()
{
	__hook(&Collider::OnCollision, &mainCollider, &Player::WasHitByEnemy);
	__hook(&Collider::OnCollision, &attackCollider, &Player::HasHitEnemy);
	__hook(&Collider::OnCollision, &attackCollider, &Player::HandleFloorCollision);
	__hook(&Collider::OnCollision, &mainCollider, &Player::HandleRoofCollision);
	__hook(&Collider::DuringCollision, &attackCollider, &Player::HandleFloorCollision);
	__hook(&Collider::DuringCollision, &mainCollider, &Player::HandleFloorCollision);
	__hook(&Collider::OnEscape, &mainCollider, &Player::EscapeFloorCollision);
	__hook(&Collider::OnEscape, &attackCollider, &Player::EscapeFloorCollision);
	__hook(&Collider::OnCollision, &mainCollider, &Player::EndGame);
	__hook(&Collider::OnCollision, &attackCollider, &Player::EndGame);
}

void Player::WasHitByEnemy(Collider* t_enemy_collider, Collider* t_collider_hit)
{
	// If the main collider of the player was hit by an enemy, run the code
	if (!isHit && t_enemy_collider->GetObjectBelongingTo()->GetType() == "Enemy")
	{
		// Make the player jump back from the hit
		hasJumped = true;
		Unground();
		SetVelocity(glm::vec2((GetPosition().x - t_enemy_collider->GetObjectBelongingTo()->GetPosition().x)*1.5, 50));

		// Deal 20 damage to the player and set the isHit flag
		Damage(20);
		isHit = true;
	}
}

void Player::HasHitEnemy(Collider* t_enemy_collider, Collider* t_friendly_collider)
{
	// If the player hit an enemy with the attack collider and hasn't been hit back, force a jump (possibly obsolete)
	if (t_enemy_collider->GetObjectBelongingTo()->GetType() == "Enemy" && t_enemy_collider->GetCollisionState(&mainCollider) == CollisionState::None)
	{
		ForceJump(t_enemy_collider);
	}
}

void Player::HandleFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	// Check for the type of floor collision if the other collider is a floor
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor"  && t_friendly_collider != &mainCollider && !hasJumped)
	{
		// The player has not jumped this frame and has landed on the floor (with the bottom collider)
		if (t_friendly_collider->GetPosition().y >= t_other_collider->GetPosition().y + (t_other_collider->GetDimensions().y) - 20)
		{
			// Stop the vertical movement of the player and ground them to the floor
			velocity.y <= 0 ? Ground(t_other_collider->GetPosition().y + (t_other_collider->GetDimensions().y) - 0.1) : velocity.x = 0;
		}

		// The player did not land on the floor, so check if he hit the sides
		else
		{
			// The player hit the left side of a wall, so stop their horizontal movement and move them out of the collision
			if (t_friendly_collider->GetPosition().x + t_friendly_collider->GetDimensions().x / 2 <= (t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x) && velocity.x > 0)
			{
				position = glm::vec2(t_other_collider->GetPosition().x - t_friendly_collider->GetDimensions().x - t_friendly_collider->GetOffset().x, position.y);
				velocity = glm::vec2(0, velocity.y);
				acceleration = glm::vec2(0, acceleration.y);
			}
			
			// The player hit the right side of a wall, so stop their horizontal movement and move them out of the collision
			if (t_friendly_collider->GetPosition().x >= (t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x / 2) && velocity.x < 0)
			{
				position = glm::vec2(t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x - t_friendly_collider->GetOffset().x, position.y);
				velocity = glm::vec2(0, velocity.y);
				acceleration = glm::vec2(0, acceleration.y);
			}
		}
	}
}

void Player::HandleRoofCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	// the player hit the bottom of a floor (a roof) so take them out of the collision and set their vertical velocity downward
	if (t_friendly_collider->GetPosition().y + t_friendly_collider->GetDimensions().y / 2 <= t_other_collider->GetPosition().y && t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		position.y -= (t_friendly_collider->GetPosition().y + t_friendly_collider->GetDimensions().y) - (t_other_collider->GetPosition().y) - 1;
		velocity.y = -20;
	}
}

void Player::EscapeFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	// The player escaped the floor collision, so enable vertical physics
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		Unground();
	}
}

void Player::EndGame(Collider* t_other_collider, Collider* t_friendly_collider)
{
	// The player managed to end the game successfully, so add score and end the game
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "EndGame")
	{
		Game::GetInstance()->AddScore(500);
		Game::GetInstance()->EndGame(t_other_collider, t_friendly_collider);
	}
}

void Player::Update(const float t_delta_time)
{
	// Stop moving when no movements controls are pressed for the direction (does not include acceleration)
	if ((InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::Released || InputHandler::GetKeyState(SDLK_RIGHT) == KeyState::None) 
		&& (InputHandler::GetKeyState(SDLK_LEFT) == KeyState::Released || InputHandler::GetKeyState(SDLK_LEFT) == KeyState::None) &&
		!isHit)
	{
		this->velocity.x = 0;
	}
	
	// If the horizontal distance between the middle of the camera and the player is more than 50 in game units, start following the player with the camera
	if (abs(instance->GetPosition().x - Game::GetInstance()->MainCamera.GetPosition().x) > 50 &&
		Game::GetInstance()->MainCamera.GetPosition().x - Game::GetInstance()->MainCamera.GetScreenDimensions().x / 2 >= 0 &&
		Game::GetInstance()->MainCamera.GetPosition().x + Game::GetInstance()->MainCamera.GetScreenDimensions().x / 2 < 10000 - GetDimensions().x / 2)
	{
		Game::GetInstance()->MainCamera.SetPosition(glm::vec2(Player::GetInstance()->GetPosition().x + (50 * Compare(Game::GetInstance()->MainCamera.GetPosition().x, Player::GetInstance()->GetPosition().x)), Game::GetInstance()->MainCamera.GetPosition().y));
		if (Game::GetInstance()->MainCamera.GetPosition().x - Game::GetInstance()->MainCamera.GetScreenDimensions().x / 2 < 0)
		{
			Game::GetInstance()->MainCamera.SetPosition(glm::vec2(Game::GetInstance()->MainCamera.GetScreenDimensions().x / 2, Game::GetInstance()->MainCamera.GetPosition().y));
		}
	}

	// If the vertical distance between the middle of the camera and the player is more than 50 in game units, start following the player with the camera
	if (abs(instance->GetPosition().y - Game::GetInstance()->MainCamera.GetPosition().y) > 60 && Game::GetInstance()->MainCamera.GetPosition().y - Game::GetInstance()->MainCamera.GetScreenDimensions().y / 2 >= 0)
	{
		Game::GetInstance()->MainCamera.SetPosition(glm::vec2(Game::GetInstance()->MainCamera.GetPosition().x, Player::GetInstance()->GetPosition().y + (60 * Compare(Game::GetInstance()->MainCamera.GetPosition().y, Player::GetInstance()->GetPosition().y))));
		
		if (Game::GetInstance()->MainCamera.GetPosition().y - Game::GetInstance()->MainCamera.GetScreenDimensions().y / 2 < 0)
		{
			Game::GetInstance()->MainCamera.SetPosition(glm::vec2(Game::GetInstance()->MainCamera.GetPosition().x, Game::GetInstance()->MainCamera.GetScreenDimensions().y / 2));
		}
	}

	// Handle the rest of the update with the characte implementation
	Character::Update(t_delta_time);
}

Player::~Player()
{
	// If the player is destroyed, unregister all of their colliders
	for (Collider* collider : colliders)
	{
		CollisionManager::GetInstance()->UnregisterCollider(collider);
	}

	// Pause the game while the end screen is up
	Game::GetInstance()->TogglePause(0);
}

Player* Player::GetInstance()
{
	// Return the instance of the player. If one does not exist, use the passed arguments to initialize them
	if (!instance)
	{
		instance = new Player(TextureManager::GetInstance()->GetTexture("grass"), glm::vec2(500, 300));
	}
	return instance;
}

Player* Player::GetInstance(Texture* t_texture_to_use)
{
	// Return the instance of the player. If one does not exist, use the passed arguments to initialize them
	if (!instance)
	{
		instance = new Player(t_texture_to_use, glm::vec2(500, 300));
	}
	return instance;
}

Player* Player::GetInstance(Texture* t_texture_to_use, glm::vec2 t_new_position)
{
	// Return the instance of the player. If one does not exist, use the passed arguments to initialize them
	if (!instance)
	{
		instance = new Player(t_texture_to_use, t_new_position);
	}
	return instance;
}

Player* Player::GetInstance(Texture* t_texture_to_use, glm::vec2 t_new_position, Rect t_custom_collider_dimensions)
{
	// Return the instance of the player. If one does not exist, use the passed arguments to initialize them
	if (!instance)
	{
		instance = new Player(t_texture_to_use, t_new_position, t_custom_collider_dimensions);
	}
	return instance;
}