#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "EntityManager.h"
#include "Destructible.h"
#include "Barrel.h"
#include "Trigger.h"
#include "Enemy.h"
#include "Player.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneStage2Platform.h"
#include "ModuleFadeToBlack.h"

#include "SDL\include\SDL.h"
#include "SDL_image\include\SDL_image.h"
#include <string>
#include <sstream>

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

	if (trainArrival == 0)
		trainArrival = App->audio->LoadFx("ff/Audio/sounds/train001.wav");

	App->collision->Enable();

	App->audio->PlayMusic("ff/audio/stage2subway.ogg", 1.0f);

	player = (Player*)App->manager->Create(PLAYER);

	trigger = (Trigger *)App->manager->Create(TRAINTRIGGER);
	trigger->position.x = 350;
	trigger->position.y = 0;
	trigger->collider->SetPos(trigger->position.x, trigger->position.y);

	trigger2 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger2->position.x = 200;
	trigger2->position.y = 0;
	trigger2->collider->SetPos(trigger2->position.x, trigger2->position.y);

	trigger3 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger3->position.x = 220;
	trigger3->position.y = 0;
	trigger3->collider->SetPos(trigger3->position.x, trigger3->position.y);

	trigger4 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger4->position.x = 490;
	trigger4->position.y = 0;
	trigger4->collider->SetPos(trigger4->position.x, trigger4->position.y);

	trigger5 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger5->position.x = 500;
	trigger5->position.y = 0;
	trigger5->collider->SetPos(trigger5->position.x, trigger5->position.y);

	trigger6 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger6->position.x = 740;
	trigger6->position.y = 0;
	trigger6->collider->SetPos(trigger6->position.x, trigger6->position.y);

	trigger7 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger7->position.x = 750;
	trigger7->position.y = 0;
	trigger7->collider->SetPos(trigger7->position.x, trigger7->position.y);

	trigger8 = (Trigger *)App->manager->Create(ENEMYTRIGGER);
	trigger8->position.x = 760;
	trigger8->position.y = 0;
	trigger8->collider->SetPos(trigger8->position.x, trigger8->position.y);

	endingTrigger = (Trigger *)App->manager->Create(ENDINGTRIGGER);
	endingTrigger->position.x = 780;
	endingTrigger->position.y = 0;
	endingTrigger->collider->SetPos(endingTrigger->position.x, endingTrigger->position.y);
	
	barrel1 = (Barrel *)App->manager->Create(BARREL);
	barrel1->position.x = 400;
	barrel1->position.y = 120;
	barrel1->collider->SetPos(barrel1->position.x, barrel1->position.y);
	
	barrel2 = (Barrel *)App->manager->Create(BARREL);
	barrel2->position.x = 500;
	barrel2->position.y = 100;
	barrel2->collider->SetPos(barrel2->position.x, barrel2->position.y);

	barrel3 = (Barrel *)App->manager->Create(BARREL);
	barrel3->position.x = 850;
	barrel3->position.y = 110;
	barrel3->collider->SetPos(barrel3->position.x, barrel3->position.y);
	
	return true;
}

// UnLoad assets
bool ModuleSceneStage2Platform::CleanUp()
{
	LOG("Unloading platform scene");
	App->textures->Unload(graphics);
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneStage2Platform::Update()
{
	if (ending) {
		App->scene_platform->player->lockCamera = true;
		int i = App->manager->Find(ENEMY);
		if (i == 0 && App->fade->isFading() == false) {
			LOG("YOU WIN");
			App->fade->FadeToBlack((Module*)App->scene_ending, this, 3.0f);
		}
	}

	if (player->to_delete && App->fade->isFading() == false) {
		LOG("YOU LOSE");
		App->fade->FadeToBlack((Module*)App->scene_over, this, 3.0f);
	}
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

bool ModuleSceneStage2Platform::SpawnEnemy(int x, int y) {
	Enemy* enemy = (Enemy *)App->manager->Create(ENEMY);
	enemy->position.x = x;
	enemy->position.y = y;
	return true;
}