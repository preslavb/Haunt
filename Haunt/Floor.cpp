#include "Floor.h"

Floor::Floor(Texture* t_texture_to_use, glm::vec2 t_new_position) : GameObject(t_texture_to_use, t_new_position), floorCollider(t_new_position, Rect(glm::vec2(0, 0), glm::vec2(500, 500)), this)
{
	type = "Floor";
	HookCollisionEvents();
}

Floor::Floor(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_dimensions) : GameObject(t_texture_to_use, t_new_position), floorCollider(t_new_position, Rect(glm::vec2(0, 0), t_new_dimensions), this)
{
	type = "Floor";
	dimensions = (t_new_dimensions);
	floorCollider.SetCollisionDistance(sqrt(pow(dimensions.x, 2) + pow(dimensions.y, 2)));
	HookCollisionEvents();
}

Floor::~Floor()
{
}

void Floor::HookCollisionEvents()
{
	//__hook(&Collider::OnCollision, &floorCollider, &Floor::HandleCollision);
	//__hook(&Collider::DuringCollision, &floorCollider, &Floor::HandleCollision);
	//__hook(&Collider::OnEscape, &floorCollider, &Floor::HandleEscape);
}

void Floor::HandleCollision(Collider* t_other_collider)
{
	//if (t_other_collider->GetObjectBelongingTo()->GetPosition().y >= position.y + dimensions.y - 20 && t_other_collider->GetObjectBelongingTo()->GetType() != "Floor")
	//{
	//	t_other_collider->GetObjectBelongingTo()->Ground(position.y + dimensions.y);
	//}
	//else
	//{
	//	t_other_collider->GetObjectBelongingTo()->SetVelocity(glm::vec2(0, t_other_collider->GetObjectBelongingTo()->GetVelocity().y));
	//	if (t_other_collider->GetObjectBelongingTo()->GetType() == "Player") std::cout << "Hit side" << std::endl;
	//	//if (t_other_collider->GetObjectBelongingTo()->GetPosition().x <= position.x)
	//	//{
	//	//	t_other_collider->GetObjectBelongingTo()->SetPosition(glm::vec2(position.x - dimensions.x /2, t_other_collider->GetObjectBelongingTo()->GetPosition().y));
	//	//}

	//	//else
	//	//{
	//	//	t_other_collider->GetObjectBelongingTo()->SetPosition(glm::vec2(position.x + (dimensions.x / 2) + t_other_collider->GetObjectBelongingTo()->GetTexture()->GetTextureWidth() / 2, t_other_collider->GetObjectBelongingTo()->GetPosition().y));
	//	//}
	//}
}

void Floor::HandleEscape(Collider* t_other_collider)
{
	//t_other_collider->GetObjectBelongingTo()->Unground();
}
