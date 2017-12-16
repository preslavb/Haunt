#include "Character.h"
#include "Game.h"
#include "Engine/CollisionManager.h"
#include "Engine/GarbageDestroyer.h"
#include "Engine/SoundsManager.h"

void Character::HookCharacterCollisionEvents()
{
	// Set the ground and unground handlers for the main collider collision events
	__hook(&Collider::OnCollision, &mainCollider, &Character::HandleFloorCollision);
	__hook(&Collider::OnEscape, &mainCollider, &Character::EscapeFloorCollision);
}

// Constructors, using the Dynamic constructors
Character::Character(Texture* t_texture_to_use, Rect t_custom_collider_dimensions) : Dynamic(t_texture_to_use), mainCollider(glm::vec2(0, 0), t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(50, 50)), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, Rect t_custom_collider_dimensions) : Dynamic(t_texture_to_use, t_new_position), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, Rect t_custom_collider_dimensions) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const int t_new_depth, Rect t_custom_collider_dimensions) : Dynamic(
	t_texture_to_use, t_new_position, t_new_depth), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = 100;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::Character(Texture* t_texture_to_use, const glm::vec2 t_new_position, const float t_new_rotation, const int t_new_health, Rect t_custom_collider_dimensions) : Dynamic(
	t_texture_to_use, t_new_position, t_new_rotation), mainCollider(t_new_position, t_custom_collider_dimensions.IsValid() ? t_custom_collider_dimensions : Rect(glm::vec2(0, 0), glm::vec2(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())), this)
{
	type = "Character";
	this->health = t_new_health;
	colliders.push_back(&mainCollider);
	HookCharacterCollisionEvents();
}

Character::~Character()
{
	// Find the current object in the GameObject vector in the game and erase it
	for (vector<GameObject*>::iterator it = Game::GetInstance()->GetGameObjects()->begin(); it != Game::GetInstance()->GetGameObjects()->end(); ++it)
	{
		if ((*it) == this)
		{
			auto gameObjects = Game::GetInstance()->GetGameObjects();
			gameObjects->erase(it);
			break;
		}
	}
}

void Character::MoveRight(float t_delta_time)
{
	// Set the flag for moving in the direction
	this->isMovingRight = true;
	this->isMoving = true;

	// If the character isn't currently moving in the opposite direction, calculate the velocity and acceleration to move with
	if (!isMovingLeft && !isHit)
	{
		// Play the movement sound for the player if the object is the player (should be reworked if there are more types of game objects)
		type == "Player" ? SoundsManager::GetInstance()->PlaySoundEffectContinuous("Whoosh") : 0;

		// Set the initial velocity to the base speed
		this->velocity.x = baseSpeed;

		// Increment the acceleration by the normal run acceleration of the character, scaled by the meter value defined in constants and scaled by delta time, so that movement is uniform for all framerates
		if (this->acceleration.x < MAX_ACCELERATION)
		{
			this->acceleration.x += RUN_ACCELERATION * _METER * t_delta_time;
		}

		// Set the texture direction to draw to right
		this->currentDirection = Direction::Right;
	}
}

void Character::MoveLeft(float t_delta_time)
{
	// Set the flag for moving in the direction
	this->isMovingLeft = true;
	this->isMoving = true;

	// If the character isn't currently moving in the opposite direction, calculate the velocity and acceleration to move with
	if (!isMovingRight && !isHit)
	{
		// Play the movement sound for the player if the object is the player (should be reworked if there are more types of game objects)
		type == "Player" ? SoundsManager::GetInstance()->PlaySoundEffectContinuous("Whoosh") : 0;

		// Set the initial velocity to the opposite base speed
		this->velocity.x = -baseSpeed;

		// Decrement the acceleration by the normal run acceleration of the character, scaled by the meter value defined in constants and scaled by delta time, so that movement is uniform for all framerates
		if (this->acceleration.x > -MAX_ACCELERATION)
		{
			this->acceleration.x -= RUN_ACCELERATION * _METER * t_delta_time;
		}

		// Set the texture direction to draw to left
		this->currentDirection = Direction::Left;
	}
}

void Character::StopMoving(float t_delta_time)
{
	// Stop playing the movement sound effect for the player
	type == "Player" ? SoundsManager::GetInstance()->StopSoundEffect("Whoosh") : 0;

	// Disable all movement flags
	this->isMoving = false;
	this->isMovingLeft = false;
	this->isMovingRight = false;
}

void Character::Jump(float t_delta_time)
{
	// If the character is currently on the ground, set the vertical velocity to the jump velocity and set the appropriate flags
	if (grounded)
	{
		// Play the jump sound (this is supposed to be just for the player but since enemies in the game don't jump, the specification isn't necessary)
		SoundsManager::GetInstance()->PlaySoundEffect("Jump");
		this->grounded = false;
		this->hasJumped = true;
		this->velocity.y = JUMP_FORCE;
	}
}

// Force a jump even if the character isn't grounded
void Character::ForceJump(Collider* t_enemy_collider)
{
	// If the collision that foced the jump involved an enemy and the player/character attacking wasn't hit in the interaction, force the jump
	if (t_enemy_collider->GetObjectBelongingTo()->GetType() == "Enemy")
	{
		if (!isHit)
		{
			this->grounded = false;
			this->hasJumped = true;
			this->velocity.y = JUMP_FORCE_HIT;
		}
	}
}

void Character::LimitJump(float t_delta_time)
{
	// If the character is moving upward faster than the jump limit when the key was released, limit the velocity and continue to apply gravity afterwards (this enables the player to control their jump height)
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
		if (this->acceleration.x - _FRICTION * _METER * Compare(acceleration.x, 0) * t_delta_time < 0 && Compare(acceleration.x, 0) >= 0)
		{
			acceleration.x = 0;
		}
		else if (this->acceleration.x - (_FRICTION * _METER * Compare(acceleration.x, 0) * t_delta_time) > 0 && Compare(acceleration.x, 0) < 0)
		{
			acceleration.x = 0;
		}
		// Otherwise, apply friction to their acceleration value, scaled by the meter value and the delta time
		else
		{
			this->acceleration.x -= _FRICTION * _METER * Compare(acceleration.x, 0) * t_delta_time;
		}
	}

	// If the character is not grounded, apply the force of gravity, based on the time since the last frame. If they are, set their y velocity to 0
	if (!grounded)
	{
		this->velocity.y -= _GRAVITY * _METER * t_delta_time;

		// If a character falls below the screen bottom, they die
		if (position.y + dimensions.y < 0)
		{
			Die();
		}
	}
	// Otherwise, the character isn't moving deliberately so set their velocity to 0
	else
	{
		this->velocity.y = 0;
	}

	// Move the character based on their velocity and acceleration
	this->Move((this->velocity + this->acceleration) * _METER * t_delta_time);

	// Jump can only happen in the frame that it was pressed, so disable it afterwards
	hasJumped = false;
}

void Character::Ground(float t_ground_height)
{
	// If the character hasn't jumped this frame, ground them to the specified ground height
	if (!hasJumped)
	{
		grounded = true;
		isHit = false;
		this->SetPosition(glm::vec2(this->GetPosition().x, t_ground_height));
	}
}

void Character::Unground()
{
	// Enable vertical physics for the character
	grounded = false;
}

void Character::Move(const glm::vec2 t_offset)
{
	// Offset the object by the specified std::vec2
	this->SetPosition(this->GetPosition() + t_offset);

	// Move the colliders to the new position of the object, and offset them as they were before
	for (Collider* collider : colliders)
	{
		collider->SetPosition(position + collider->GetOffset());
	}
}

void Character::SetPosition(glm::vec2 t_new_position)
{
	// Move the character to the specified position
	position = t_new_position;

	// Move the colliders to the new position of the object, and offset them as they were before
	for (Collider* collider : colliders)
	{
		collider->SetPosition(t_new_position + collider->GetOffset());
	}
}

void Character::WasHitByPlayer(Collider* t_player_collider, Collider* t_collider_hit)
{
	// If the player hit the character, and the player main collider wasn't hit back, apply the damage to the character and force a jump on the player
	if (Player::GetInstance()->GetHitCollider()->GetCollisionState(&mainCollider) == CollisionState::None && t_player_collider->GetObjectBelongingTo()->GetType() == "Player")
	{
		std::cout << "Character was hit by the player, dealing 100 DMG" << std::endl;
		Player::GetInstance()->ForceJump(&mainCollider);
		Damage(100);
	}
}

void Character::HandleFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	// If the collision is with a floor, increment the number of floors colliding with right now and check the collision type
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		floorsCollidingWith++;

		// The character fell on top of the floor, so ground them to the floor
		if (t_friendly_collider->GetPosition().y >= t_other_collider->GetPosition().y + (t_other_collider->GetDimensions().y) - 20)
		{
			velocity.y <= 0 ? Ground(t_other_collider->GetPosition().y + (t_other_collider->GetDimensions().y)) : velocity.x = 0;
		}

		// Otherwise, the collision happened to the side of a floor, acting as a wall, so stop the horizontal movement of the character
		else
		{
			if (t_friendly_collider->GetPosition().x <= (t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x / 2))
			{
				// Turn around when colliding with a wall
				isMovingLeft = true;
				velocity = glm::vec2(-velocity.x, velocity.y);
				acceleration = glm::vec2(-acceleration.x, acceleration.y);

				// Make sure that the character isn't stuck inside the wall by moving them out of the collider
				position = glm::vec2(t_other_collider->GetPosition().x - t_friendly_collider->GetDimensions().x, position.y);
			}
			else if (t_friendly_collider->GetPosition().x >= (t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x / 2))
			{
				// Turn around when colliding with a wall
				isMovingLeft = false;
				velocity = glm::vec2(-velocity.x, velocity.y);
				acceleration = glm::vec2(-acceleration.x, acceleration.y);

				// Make sure that the character isn't stuck inside the wall by moving them out of the collider
				position = glm::vec2(t_other_collider->GetPosition().x + t_other_collider->GetDimensions().x, position.y);
			}
		}
	}
}

void Character::EscapeFloorCollision(Collider* t_other_collider, Collider* t_friendly_collider)
{
	// If the character escaped from a floor collision, check if there are any other floors that the character is colliding
	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Floor")
	{
		floorsCollidingWith--;

		// If there aren't any other floors colliding with this character, unground them and let them fall
		if (floorsCollidingWith <= 0) Unground();
	}
}

bool Character::IsHit()
{
	return isHit;
}

void Character::Damage(const int t_amount_of_damage)
{
	// Decrement the health of the character by the amount of damage passed to the function
	this->health -= t_amount_of_damage;
	this->isHit = true;

	// If the health falls below 0, kill the character
	if (health <= 0)
	{
		Die();
	}
}

void Character::Die()
{
	// Play the squash sound for dying characters
	SoundsManager::GetInstance()->PlaySoundEffect("Squash");

	// If the player died, end the game and display the score
	type == "Player" ? Game::GetInstance()->EndGame(nullptr, nullptr) : 0;

	// Destroy the character that just died
	GarbageDestroyer<Character*>::GetInstance()->Destroy(this);
}

Collider* Character::GetMainCollider()
{
	return &mainCollider;
}
