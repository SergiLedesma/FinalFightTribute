#include "Application.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Barrel.h"
#include "Weapon.h"
#include "Food.h"
#include "Score.h"
#include "TrainTrigger.h"
#include "EnemyTrigger.h"

EntityManager::EntityManager(bool active) : Module(active)
{
}


EntityManager::~EntityManager()
{
}

bool EntityManager::Start()
{
	for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
		(*it)->Start();
	}
	return true;
}

update_status EntityManager::PreUpdate()
{
	// Remove all entities scheduled for deletion
	for (list<Entity*>::iterator it = entityList.begin(); it != entityList.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = entityList.erase(it);
		}
		else
			++it;
	}
	return UPDATE_CONTINUE;
}

update_status EntityManager::Update()
{
	for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ) {
		if (*it != nullptr) {
			(*it)->Update();
			++it;
		}
	}
	return UPDATE_CONTINUE;
}

bool EntityManager::CleanUp()
{
	for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
		RELEASE(*it);
	}
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
	case TTRIGGER:
		newEntity = new TrainTrigger();
		break;
	case ETRIGGER:
		newEntity = new EnemyTrigger();
		break;
	case WEAPON:
		newEntity = new Weapon();
		break;
	case FOOD:
		newEntity = new Food();
		break;
	case SCORE:
		newEntity = new Score();
		break;
	default:
		newEntity = nullptr;
		LOG("Entity not created");
		break;
	}
	if (newEntity != nullptr) {
		LOG("Entity created");
		entityList.push_back(newEntity);
	}
	newEntity->Start();
	return newEntity;
}