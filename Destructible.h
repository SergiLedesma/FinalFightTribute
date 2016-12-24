#pragma once
#include "Entity.h"
class Destructible :
	public Entity
{
public:
	Destructible();
	~Destructible();
	update_status Update();
	void OnCollision();
	FrameInfo destroyedRect;
	FrameInfo nonDestroyedRect;
	bool destroyed = false;
};

