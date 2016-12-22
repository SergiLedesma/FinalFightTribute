#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "EntityManager.h"
#include "ModuleSceneStage2Platform.h"

ModuleSceneStage2Platform::ModuleSceneStage2Platform(bool active) : Module(active)
{
	background.x = 7;
	background.y = 4;
	background.w = 1119;
	background.h = 195;

	train.x = 7;
	train.y = 207;
	train.w = 1579;
	train.h = 139;

	train2.x = 50;
	train2.y = 207;
	train2.w = 1579;
	train2.h = 139;

	trainSpeedDecay = baseTrainSpeedDecay;
	trainEndPosition = -420 - train2.w;
}

ModuleSceneStage2Platform::~ModuleSceneStage2Platform()
{}

// Load assets
bool ModuleSceneStage2Platform::Start()
{
	LOG("Loading platform scene");

	graphics = App->textures->Load("ff/sprites/Stage2NoBackground.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	App->audio->PlayMusic("ff/audio/stage2subway.ogg", 1.0f);
	
	App->manager->Create(PLAYER);

	//App->collision->AddCollider({ 0, 224, 3930, 16 }, WALL, nullptr);
	
	return true;
}

// UnLoad assets
bool ModuleSceneStage2Platform::CleanUp()
{
	LOG("Unloading platform scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneStage2Platform::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;

	App->player->position.x += 0;
	App->renderer->camera.x -= 0;

	// Draw background --------------------------------------
	App->renderer->BlitStatic(graphics, 0, tremorOffset, &background);

	// Draw train --------------------------------------
	if (playTrainAnim) {
		playTrainAnim = ChangeTrainPosition(trainSpeed);
		LOG("%d", trainSpeed);
		if (trainSpeedDecay <= 0) {
			if (trainSpeed > 2) {
				trainSpeed -= 1;
			}
			baseTrainSpeedDecay /= 2;
			trainSpeedDecay = baseTrainSpeedDecay;
		}
		trainSpeedDecay--;

		if (tremorSpan <= 0) {
			tremorSpan = 5;
			if (tremorOffset == 2) {
				tremorOffset = 0;
			}
			else {
				tremorOffset = 2;
			}
		}
		tremorSpan--;
	}
	else {
		tremorOffset = 0;
	}

	

	App->renderer->BlitStatic(graphics, trainCurrentPosition, 0, &train);
	App->renderer->BlitStatic(graphics, trainCurrentPosition + train.w, 0, &train2);

	return UPDATE_CONTINUE;
}

bool ModuleSceneStage2Platform::ChangeTrainPosition(int trainSpeed) {
	bool ret;
	if (trainCurrentPosition > trainEndPosition) {
		trainCurrentPosition -= trainSpeed;
		ret = true;
	}
	else {
		ret = false;
	}
	return ret;
}