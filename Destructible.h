#pragma once
#include "Entity.h"
class Destructible :
	public Entity
{
public:
	Destructible();
	~Destructible();
	update_status Update();
};

