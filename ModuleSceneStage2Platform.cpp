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
#include "Trigger.h"
#include "Enemy.h"
#include "ModuleSceneStage2Platform.h"

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

	App->particles->Enable();
	App->collision->Enable();
	player = (Player*)App->manager->Create(PLAYER);

	App->audio->PlayMusic("ff/audio/stage2subway.ogg", 1.0f);

	trigger = (Trigger *)App->manager->Create(TTRIGGER);
	trigger->position.x = 350;
	trigger->position.y = 0;
	trigger->collider->SetPos(trigger->position.x, trigger->position.y);

	trigger2 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger2->position.x = 200;
	trigger2->position.y = 0;
	trigger2->collider->SetPos(trigger2->position.x, trigger2->position.y);

	trigger3 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger3->position.x = 200;
	trigger3->position.y = 0;
	trigger3->collider->SetPos(trigger3->position.x, trigger3->position.y);

	trigger4 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger4->position.x = 500;
	trigger4->position.y = 0;
	trigger4->collider->SetPos(trigger4->position.x, trigger4->position.y);

	trigger5 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger5->position.x = 500;
	trigger5->position.y = 0;
	trigger5->collider->SetPos(trigger5->position.x, trigger5->position.y);

	trigger6 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger6->position.x = 800;
	trigger6->position.y = 0;
	trigger6->collider->SetPos(trigger6->position.x, trigger6->position.y);

	trigger7 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger7->position.x = 800;
	trigger7->position.y = 0;
	trigger7->collider->SetPos(trigger7->position.x, trigger7->position.y);

	trigger8 = (Trigger *)App->manager->Create(ETRIGGER);
	trigger8->position.x = 800;
	trigger8->position.y = 0;
	trigger8->collider->SetPos(trigger8->position.x, trigger8->position.y);
	
	barrel1 = (Barrel *)App->manager->Create(BARREL);
	barrel1->position.x = 400;
	barrel1->position.y = 120;
	barrel1->collider->SetPos(barrel1->position.x, barrel1->position.y);
	
	barrel2 = (Barrel *)App->manager->Create(BARREL);
	barrel2->position.x = 500;
	barrel2->position.y = 100;
	barrel2->collider->SetPos(barrel2->position.x, barrel2->position.y);

	barrel2 = (Barrel *)App->manager->Create(BARREL);
	barrel2->position.x = 500;
	barrel2->position.y = 100;
	barrel2->collider->SetPos(barrel2->position.x, barrel2->position.y);

	//App->collision->AddCollider({ 0, 224, 3930, 16 }, WALL, nullptr);
	
	return true;
}

// UnLoad assets
bool ModuleSceneStage2Platform::CleanUp()
{
	LOG("Unloading platform scene");
	for (Enemy* iter : enemies) {
		iter->to_delete = true;
	}
	trigger->to_delete = true;
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
	if (trigger2->to_delete == true) {
		int i = 0;
		for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
			if (!(*it)->to_delete) {
				i++;
			}
		}
		if (i == 0) {
			LOG("YOU WIN");
		}
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
	enemies.push_back(enemy);
	return true;
}