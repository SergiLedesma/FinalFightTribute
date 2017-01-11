#include <map>
#include "Application.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Barrel.h"
#include "TrainTrigger.h"
#include "EnemyTrigger.h"
#include "EndingTrigger.h"

EntityManager::EntityManager(bool active) : Module(active)
{
}


EntityManager::~EntityManager()
{
}

bool EntityManager::Start()
{
	for (std::map<Entity*, EntityType>::iterator it = entities.begin(); it != entities.end(); ++it) {
		(*it).first->Start();
	}
	return true;
}

update_status EntityManager::PreUpdate()
{
	// Remove all entities scheduled for deletion
	for (std::map<Entity*, EntityType>::iterator it = entities.begin(); it != entities.end(); ) {
		if ((*it).first->to_delete == true)
		{
			Entity* entity = (*it).first;
			entity->CleanUp();
			RELEASE(entity);
			it = entities.erase(it);
		}
		else
			++it;
	}
	return UPDATE_CONTINUE;
}

update_status EntityManager::Update()
{
	for (std::map<Entity*, EntityType>::iterator it = entities.begin(); it != entities.end();) {
		if ((*it).first != nullptr) {
			(*it).first->Update();
			++it;
		}
	}
	return UPDATE_CONTINUE;
}

bool EntityManager::CleanUp()
{
	for (std::map<Entity*, EntityType>::iterator it = entities.begin(); it != entities.end(); ++it) {
		Entity* entity = (*it).first;
		(*it).first->CleanUp();
		RELEASE(entity);
	}
	entities.clear();
	return true;
}

Entity * EntityManager::Create(EntityType type)
{
	Entity * newEntity;

	switch (type) {
	case PLAYER:
		newEntity = new Player();
		break;
	case ENEMY:
		newEntity = new Enemy();
		break;
	case BARREL:
		newEntity = new Barrel();
		break;
	case TRAINTRIGGER:
		newEntity = new TrainTrigger();
		break;
	case ENEMYTRIGGER:
		newEntity = new EnemyTrigger();
		break;
	case ENDINGTRIGGER:
		newEntity = new EndingTrigger();
		break;
	default:
		newEntity = nullptr;
		LOG("Entity not created");
		break;
	}
	if (newEntity != nullptr) {
		LOG("Entity created");
		entities.insert({ newEntity, type });
	}
	newEntity->Start();
	return newEntity;
}

int EntityManager::Find(EntityType type) {
	int retValue = 0;
	for (std::map<Entity*, EntityType>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if ((*it).second == type) {
			retValue++;
		}
	}
	return retValue;
}