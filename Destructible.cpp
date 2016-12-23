#include "Destructible.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleSceneStage2Platform.h"
#include "SDL\include\SDL_render.h"


Destructible::Destructible()
{
	graphics = App->textures->Load("ff/Sprites/Items.png");
	destroyed = false;
	position.x = 500;
	position.y = 120;

	rect.frame.x = 30;
	rect.frame.y = 178;
	rect.frame.w = 32;
	rect.frame.h = 62;
}


Destructible::~Destructible()
{
}

update_status Destructible::Update() {
	App->renderer->AddBlit(graphics, position.x, position.y + App->scene_platform->tremorOffset, &rect);
	
	return UPDATE_CONTINUE;
}