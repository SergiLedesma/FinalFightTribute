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
	return true;
}

update_status EntityManager::Update()
{
	return update_status();
}

void EntityManager::OnCollision()
{
}

bool EntityManager::CleanUp()
{
	return true;
}

Entity * EntityManager::Create(EntityType type)
{
	Entity * ret;

	switch (type) {
	case PLAYER:
		ret = new Player();
		break;
	default:
		break;
	}
	 return ret;
}