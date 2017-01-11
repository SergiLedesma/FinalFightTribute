#include "ModuleSceneEnding.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

ModuleSceneEnding::ModuleSceneEnding(bool active) : Module(active)
{
}

ModuleSceneEnding::~ModuleSceneEnding()
{
}

// Load assets
bool ModuleSceneEnding::Start()
{
	LOG("Loading ending scene");

	background = App->textures->Load("ff/Sprites/youWon.png");

	App->audio->PlayMusic("ff/Audio/endingTheme.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneEnding::CleanUp()
{
	LOG("Unloading ending scene");

	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleSceneEnding::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	App->renderer->AddBlit(background, 0, 0, nullptr, 1, true, true);

	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
	{
		LOG("RESTART");
		ret = UPDATE_RESTART;
	}
	else if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {
		LOG("QUIT");
		ret = UPDATE_STOP;
	}

	return ret;
}