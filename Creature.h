#pragma once
#include "Entity.h"
class Creature :
	public Entity
{
public:
	Creature();
	~Creature();

public:
	Animation* currentAnimation = nullptr;
	Animation* lastMovementAnimation = nullptr;
	Collider* collider = nullptr;
	Collider* attackCollider = nullptr;
	Animation idle;
	Animation right;
	Animation left;
};

