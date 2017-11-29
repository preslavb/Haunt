#pragma once

class Collision
{
	
};

class Collider
{
public:
	Collider();
	~Collider();

	Collision TestCollision(Collider);
};