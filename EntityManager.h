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
	bool CleanUp();

	std::list<Entity*> entityList;
	Entity * Create(EntityType type);
	bool Destroy(Entity * entity);
};

#endif //__EntityManager_H__