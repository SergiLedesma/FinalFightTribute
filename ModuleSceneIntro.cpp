#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"

ModuleSceneIntro::ModuleSceneIntro(bool active) : Module(active)
{
	startAnimation = new Animation();
	(*startAnimation).frames.push_back(FrameInfo({ 0, 0, 88, 8 }));
	(*startAnimation).frames.push_back(FrameInfo({ 0, 0, 88, 0 }));
	(*startAnimation).loop = true;
	(*startAnimation).speed = 0.03f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	RELEASE(startAnimation);
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading intro scene");

	background = App->textures->Load("ff/Sprites/intro.png");
	graphics = App->textures->Load("ff/Sprites/start.png");

	App->audio->PlayMusic("ff/Audio/intro.ogg", 1.0f);
	if (fx == 0)
		fx = App->audio->LoadFx("ff/Audio/sounds/song004.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(background);
	App->textures->Unload(graphics);
	RELEASE(startAnimation);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->AddBlit(background, 0, 0, nullptr, 1, true, true);
	App->renderer->AddBlit(graphics, SCREEN_WIDTH / 2 - (startAnimation->GetCurrentFrame().frame.w/2), SCREEN_HEIGHT - SCREEN_HEIGHT/2.5, &(startAnimation->GetCurrentFrame()));

	if (App->input->GetKey(ATTACK) == KEY_DOWN && App->fade->isFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_platform, this, 4.0f);
		App->audio->PlayMusic("ff/audio/gameStart.ogg", 0.0f);
		App->audio->PlayFx(fx);
	}

	return UPDATE_CONTINUE;
}