#pragma once
#include <map>
#include "Entity.h"
#include "MovementKeys.h"
#include "ModuleCollision.h"

class Trigger :
	public Entity
{
public:
	Trigger();
	~Trigger();
	bool Start();
	void OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType);
	void AddCollider();
	virtual void Shot() {};
};

