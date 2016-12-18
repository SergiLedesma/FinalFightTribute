#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include <functional>

using namespace std;

ModuleCollision::ModuleCollision()
{
	collisionMatrix[make_pair(PLAYER, WALL)] = true;
	collisionMatrix[make_pair(PLAYER, ENEMY)] = true;
	collisionMatrix[make_pair(PLAYER, ENEMY_SHOT)] = true;
	collisionMatrix[make_pair(PLAYER_SHOT, WALL)] = true;
	collisionMatrix[make_pair(PLAYER_SHOT, ENEMY)] = true;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	for (std::list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it) {
		for (std::list<Collider*>::iterator it2 = std::next(it, 1); it2 != colliders.end(); ++it2) {
			if ((*it)->CheckCollision(**it2)) {
				LOG("COLLISION!!");
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, CollisionType type, std::function<void()> onCollision)
{
	Collider* ret = new Collider(rect, onCollision);
	ret->type = type;

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const Collider& c) const
{
	bool ret = false;
	SDL_Rect r = c.rect;

	if (App->collision->CheckCollidingTypes(type, c.type)) {
		if ((r.x + r.w < this->rect.x) || (this->rect.x + this->rect.w < r.x)) {
			ret = false;
		}
		else if ((r.y + r.h < this->rect.y) || (this->rect.y + this->rect.h < r.y)) {
			ret = false;
		}
		else {
			ret = true;
		}
	}
	if (ret == true) {
		if (this->OnCollision != nullptr)
			this->OnCollision();
		if (c.OnCollision != nullptr)
			c.OnCollision();
	}

	return ret;
}

bool ModuleCollision::CheckCollidingTypes(CollisionType type, CollisionType otherType) {
	return (collisionMatrix[make_pair(type, otherType)] || collisionMatrix[make_pair(otherType, type)]);
}