#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "EntityManager.h"
#include "Destructible.h"
#include "Barrel.h"
#include "ModuleSceneStage2Platform.h"

ModuleSceneStage2Platform::ModuleSceneStage2Platform(bool active) : Module(active)
{
	background.frame.x = 7;
	background.frame.y = 4;
	background.frame.w = 1119;
	background.frame.h = 195;

	train.frame.x = 7;
	train.frame.y = 207;
	train.frame.w = 1579;
	train.frame.h = 139;

	train2.frame.x = 50;
	train2.frame.y = 207;
	train2.frame.w = 1579;
	train2.frame.h = 139;

	trainSpeedDecay = baseTrainSpeedDecay;
	trainEndPosition = -420 - train2.frame.w;
}

ModuleSceneStage2Platform::~ModuleSceneStage2Platform()
{}

// Load assets
bool ModuleSceneStage2Platform::Start()
{
	LOG("Loading platform scene");

	graphics = App->textures->Load("ff/sprites/Stage2NoBackground.png");

	//App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	player = (Player*)App->manager->Create(PLAYER);

	//App->audio->PlayMusic("ff/audio/stage2subway.ogg", 1.0f);
	
	barrel1 = (Barrel *)App->manager->Create(BARREL);
	barrel1->position.x = 200;
	barrel1->position.y = 120;
	barrel1->collider->SetPos(200, 120);
	
	barrel2 = (Barrel *)App->manager->Create(BARREL);
	barrel2->position.x = 250;
	barrel2->position.y = 100;
	barrel2->collider->SetPos(250, 100);

	//App->collision->AddCollider({ 0, 224, 3930, 16 }, WALL, nullptr);
	
	return true;
}

// UnLoad assets
bool ModuleSceneStage2Platform::CleanUp()
{
	LOG("Unloading platform scene");

	barrel2->to_delete = true;
	barrel1->to_delete = true;
	App->textures->Unload(graphics);
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneStage2Platform::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;

	App->renderer->camera.x -= 0;

	// Draw background --------------------------------------
	App->renderer->AddBlit(graphics, 0, tremorOffset, &background, 1.0f, true, true);

	// Draw train --------------------------------------
	if (playTrainAnim) {
		playTrainAnim = ChangeTrainPosition(trainSpeed);
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

	App->renderer->AddBlit(graphics, trainCurrentPosition, 0, &train, 1.0f, true, true);
	App->renderer->AddBlit(graphics, trainCurrentPosition + train.frame.w, 0, &train2, 1.0f, true, true);

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