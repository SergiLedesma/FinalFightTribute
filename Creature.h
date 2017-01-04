#pragma once
#include "Entity.h"
class Creature :
	public Entity
{
public:
	Creature();
	~Creature();

public:
	SDL_Texture* graphics = nullptr;
	Animation* currentAnimation = nullptr;
	Animation* lastMovementAnimation = nullptr;
	Collider* collider = nullptr;
	Animation idle;
	Animation right;
	Animation left;
};

