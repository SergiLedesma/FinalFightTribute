#ifndef __EntityManager_H__
#define __EntityManager_H__

#include "Module.h"
#include "Entity.h"


class EntityManager :
	public Module
{
public:
	EntityManager(bool active = true);
	~EntityManager();

	bool Start();
	update_status Update();
	void OnCollision();
	bool CleanUp();

	Entity * Create(EntityType type);
};

#endif //__EntityManager_H__