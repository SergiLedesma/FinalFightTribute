#include "Trigger.h"
#include "Application.h"
#include "ModuleCollision.h"



Trigger::Trigger()
{
}


Trigger::~Trigger()
{
}

bool Trigger::Start() {
	this->AddCollider();
	collider->rect.w = 20;
	collider->rect.h = SCREEN_HEIGHT;
	
	return true;
}

void Trigger::OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType)
{
	LOG("Collision on trigger");
	Shot();
	to_delete = true;
	collider->to_delete = true;
}

void Trigger::AddCollider() {
	collider = App->collision->AddCollider({ position.x, position.y, rect.frame.w, rect.frame.h }, CTRIGGER, std::bind(&Trigger::OnCollision, this, std::placeholders::_1, std::placeholders::_2));
}