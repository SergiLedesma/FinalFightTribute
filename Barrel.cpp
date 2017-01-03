#include "Barrel.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_render.h"



Barrel::Barrel()
{
}


Barrel::~Barrel()
{
}

bool Barrel::Start() {
	graphics = App->textures->Load("ff/Sprites/Items.png");
	
	nonDestroyedRect.frame.x = 30;
	nonDestroyedRect.frame.y = 178;
	nonDestroyedRect.frame.w = 32;
	nonDestroyedRect.frame.h = 62;

	destroyedRect.frame.x = 75;
	destroyedRect.frame.y = 157;
	destroyedRect.frame.w = 45;
	destroyedRect.frame.h = 95;

	this->AddCollider();
	collider->rect.w = 32;
	collider->rect.h = 62;

	destroyed = false;
	position.x = 0;
	position.y = 0;

	lifeSpan = 30;

	return true;
}