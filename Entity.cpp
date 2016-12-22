#include "Entity.h"



Entity::Entity()
{
}

Entity::~Entity()
{
}

bool Entity::Start()
{
	return false;
}

update_status Entity::Update()
{
	return update_status();
}

void Entity::OnCollision()
{
}

bool Entity::CleanUp()
{
	return false;
}
