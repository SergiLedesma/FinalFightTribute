#include "Destructible.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "Player.h"
#include "ModuleSceneStage2Platform.h"


Destructible::Destructible()
{
	
}


Destructible::~Destructible()
{
}

update_status Destructible::Update() {
	if (!destroyed) {
		rect = nonDestroyedRect;
	}
	else {
		rect = destroyedRect;
		if (animationDirection) {
			position.x += 4;
		}
		else {
			position.x -= 4;
		}
		lifeSpan--;
	}

	App->renderer->AddBlit(graphics, position.x, position.y + App->scene_platform->tremorOffset, &rect);
	if (lifeSpan <= 0) {
		to_delete = true;
	}
	return UPDATE_CONTINUE;
}

void Destructible::OnCollision(std::map<MOVEMENTKEY, bool> direction)
{
	LOG("Collision on barrel");
	
	destroyed = true;
	position.y -= 25;
	animationDirection = App->scene_platform->player->direction;
	collider->to_delete = true;
	
}

void Destructible::AddCollider() {
	collider = App->collision->AddCollider({ position.x, position.y, rect.frame.w, rect.frame.h }, CDESTRUCTIBLE, std::bind(&Destructible::OnCollision, this, std::placeholders::_1));
}