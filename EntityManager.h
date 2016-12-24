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
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Entity * Create(EntityType type);
	bool Destroy(Entity * entity);

private:
	std::list<Entity*> entityList;
};

#endif //__EntityManager_H__