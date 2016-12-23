#include "Application.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Destructible.h"
#include "Weapon.h"
#include "Food.h"
#include "Score.h"

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

update_status EntityManager::Update()
{
	for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
		(*it)->Update();
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
	case DESTRUCTIBLE:
		newEntity = new Destructible();
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

bool EntityManager::Destroy(Entity * entity)
{
	bool ret = false;
	for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
		if (*it == entity) {
			RELEASE(*it);
			ret = true;
			LOG("Entity destroyed");
			break;
		}
	}
	return ret;
}
