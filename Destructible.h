#ifndef __DESTRUCTIBLE_H__
#define __DESTRUCTIBLE_H__

#include <map>
#include "Entity.h"
#include "MovementKeys.h"
#include "ModuleCollision.h"

class Destructible :
	public Entity
{
public:
	Destructible();
	~Destructible();
	update_status Update();
	void OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType);
	void AddCollider();
	FrameInfo destroyedRect;
	FrameInfo nonDestroyedRect;
	bool destroyed = false;
	bool animationDirection = true;
};

#endif // __DESTRUCTIBLE_H__