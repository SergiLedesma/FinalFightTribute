#include "Trigger.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "EntityManager.h"
#include "ModuleSceneStage2Platform.h"



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

void Trigger::OnCollision(std::map<MOVEMENTKEY, bool> direction)
{
	LOG("Collision on trigger");
	App->scene_platform->playTrainAnim = true;
	to_delete = true;
	collider->to_delete = true;
}

void Trigger::AddCollider() {
	collider = App->collision->AddCollider({ position.x, position.y, rect.frame.w, rect.frame.h }, CTRIGGER, std::bind(&Trigger::OnCollision, this, std::placeholders::_1));
}