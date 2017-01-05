#pragma once
#include <map>
#include "Entity.h"
#include "MovementKeys.h"

class Destructible :
	public Entity
{
public:
	Destructible();
	~Destructible();
	update_status Update();
	void OnCollision(std::map<MOVEMENTKEY, bool> direction);
	void AddCollider();
	FrameInfo destroyedRect;
	FrameInfo nonDestroyedRect;
	bool destroyed = false;
};

