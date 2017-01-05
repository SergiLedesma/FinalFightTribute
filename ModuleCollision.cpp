#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "MovementKeys.h"
#include <functional>

using namespace std;

ModuleCollision::ModuleCollision()
{
	collisionMatrix[make_pair(CPLAYER, CWALL)] = true;
	collisionMatrix[make_pair(CPLAYER, CENEMY)] = true;
	collisionMatrix[make_pair(CPLAYER, CENEMY_ATTACK)] = true;
	collisionMatrix[make_pair(CPLAYER_ATTACK, CWALL)] = true;
	collisionMatrix[make_pair(CPLAYER_ATTACK, CENEMY)] = true;
	collisionMatrix[make_pair(CPLAYER_ATTACK, CDESTRUCTIBLE)] = true;
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

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, CollisionType type, std::function<void(std::map<MOVEMENTKEY, bool>)> onCollision)
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
	std::map<MOVEMENTKEY, bool> direction = {
		{RIGHT, true},
		{LEFT, true},
		{UP, true},
		{DOWN, true}
	};

	if (App->collision->CheckCollidingTypes(type, c.type)) {
		if (this->rect.x + this->rect.w < r.x) {
			direction.at(LEFT) = false;
			ret = false;
		}
		else if (r.x + r.w < this->rect.x) {
			direction.at(RIGHT) = false;
			ret = false;
		}
		else if (this->rect.y + this->rect.h < r.y) {
			direction.at(UP) = false;
			ret = false;
		}
		else if (r.y + r.h < this->rect.y) {
			direction.at(DOWN) = false;
			ret = false;
		}
		else {
			ret = true;
		}
	}
	if (ret == true) {
		for (int i = DOWN; i = UP; i++) {
			MOVEMENTKEY current = static_cast<MOVEMENTKEY>(i);
			direction;
		}
		if (this->OnCollision != nullptr)
			this->OnCollision(direction);
		if (c.OnCollision != nullptr)
			c.OnCollision(direction);
	}

	return ret;
}

bool ModuleCollision::CheckCollidingTypes(CollisionType type, CollisionType otherType) {
	return (collisionMatrix[make_pair(type, otherType)] || collisionMatrix[make_pair(otherType, type)]);
}