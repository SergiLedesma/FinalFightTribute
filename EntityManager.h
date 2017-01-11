#ifndef __EntityManager_H__
#define __EntityManager_H__

#include <map>
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

	int Find(EntityType type);

private:
	std::map<Entity*, EntityType> entities;
};

#endif //__EntityManager_H__