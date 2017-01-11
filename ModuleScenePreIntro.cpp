#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenePreIntro.h"
#include "FxLibrary.h"

ModuleScenePreIntro::ModuleScenePreIntro(bool active) : Module(active)
{
}

ModuleScenePreIntro::~ModuleScenePreIntro()
{
}

// Load assets
bool ModuleScenePreIntro::Start()
{
	LOG("Loading preintro scene");

	graphics = App->textures->Load("ff/Sprites/sergi.png");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	App->audio->PlayFx(App->fxlib->opening);

	return true;
}

// UnLoad assets
bool ModuleScenePreIntro::CleanUp()
{
	LOG("Unloading preintro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleScenePreIntro::Update()
{
	App->renderer->AddBlit(graphics, 0, -30, nullptr, 1.0f, true, true);

	if (countdown <= 0 && App->fade->isFading() == false) {
		App->fade->FadeToBlack((Module*)App->scene_intro, this, 3.0f);
	}
	else {
		countdown--;
	}

	return UPDATE_CONTINUE;
}