#include "Destructible.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SDL\include\SDL_render.h"


Destructible::Destructible()
{
	graphics = App->textures->Load("ff/Sprites/Items.png");
	destroyed = false;
	position.x = 500;
	position.y = 120;
	rect.x = 30;
	rect.y = 178;
	rect.w = 32;
	rect.h = 62;

	
}


Destructible::~Destructible()
{
}

update_status Destructible::Update() {
	App->renderer->BlitStatic(graphics, position.x, position.y, &rect);
	return UPDATE_CONTINUE;
}