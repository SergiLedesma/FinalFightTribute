#include "Destructible.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "EntityManager.h"
#include "ModuleSceneStage2Platform.h"
#include "SDL\include\SDL_render.h"


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
		position.x += 4;
		lifeSpan--;
	}

	App->renderer->AddBlit(graphics, position.x, position.y + App->scene_platform->tremorOffset, &rect);
	if (lifeSpan <= 0) {
		to_delete = true;
	}
	return UPDATE_CONTINUE;
}

void Destructible::OnCollision() {

	LOG("Collision on barrel");

	destroyed = true;
	position.y -= 25;
	collider->to_delete = true;
}