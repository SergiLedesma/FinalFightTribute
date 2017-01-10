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
	collisionMatrix[make_pair(CPLAYER, CTRIGGER)] = true;
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
			(*it)->CheckCollision(**it2);
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
		{ RIGHT, false },
		{ LEFT, false },
		{ UP, false },
		{ DOWN, false }
	};

	float w = 0.5 * (this->rect.w + c.rect.w);
	float h = 0.5 * (this->rect.h + c.rect.h);
	float dx = (this->rect.x + this->rect.w) - (c.rect.x + c.rect.w);
	float dy = (this->rect.y + this->rect.h) - (c.rect.y + c.rect.h);
	if (App->collision->CheckCollidingTypes(type, c.type)) {
		if (abs(dx) <= w && abs(dy) <= h)
		{
			// COLLISION
			float wy = w * dy;
			float hx = h * dx;

			ret = true;

			if (wy > hx) {
				if (wy > -hx) {
					// COLLISION AT THE BOTTOM
					direction.at(DOWN) = true;
				}
				else
				{
					// COLLISION ON THE LEFT
					direction.at(LEFT) = true;
				}
			}
			else
			{
				if (wy > -hx) {
					// COLLISION ON THE RIGHT
					direction.at(RIGHT) = true;
				}
				else
				{
					// COLLISION AT THE TOP
					direction.at(UP) = true;
				}
			}

			if (this->OnCollision != nullptr) {
				this->OnCollision(direction);
			}
			if (c.OnCollision != nullptr) {
				// invert direction
				for (auto i : direction) {
					if (i.second) {
						i.second = false;
					}
					else {
						i.second = true;
					}
				}
				c.OnCollision(direction);
			}
		}
	}

	return ret;
}

bool ModuleCollision::CheckCollidingTypes(CollisionType type, CollisionType otherType) {
	return (collisionMatrix[make_pair(type, otherType)] || collisionMatrix[make_pair(otherType, type)]);
}