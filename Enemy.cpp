#include <time.h>
#include "Enemy.h"
#include "Player.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneStage2Platform.h"
#include "Timer.h"
#include "SDL\include\SDL_render.h"



Enemy::Enemy()
{
	LOG("ENEMY SPAWNED");

	Life = new EnemyStateMachine(this);

	// idle animation
	idle.frames.push_back(FrameInfo({ 13, 89, 46, 77 }, 0, -8));
	idle.loop = false;
	idle.speed = 0.2f;

	// move right
	right.frames.push_back(FrameInfo({ 8, 11, 46, 71 }));
	right.frames.push_back(FrameInfo({ 58, 9, 39, 72 }));
	right.frames.push_back(FrameInfo({ 101, 9, 34, 72 }));
	//right.frames.push_back(FrameInfo({ 164, 100, 26, 88 }));
	//right.frames.push_back(FrameInfo({ 213, 101, 45, 87 }));
	//right.frames.push_back(FrameInfo({ 267, 101, 36, 86 }));
	right.loop = true;
	right.speed = 0.1f;

	// move left
	left = right;
	left.loop = true;
	left.speed = 0.1f;

	// attack
	attack.frames.push_back(FrameInfo({ 13, 89, 46, 77 }, 0, -8));
	attack.frames.push_back(FrameInfo({ 65, 87, 70, 77 }, 20, -6));
	attack.loop = false;
	attack.speed = 0.2f;
}


Enemy::~Enemy()
{
}

// Load assets
bool Enemy::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("ff/Sprites/Enemies/Dug.png");

	position.x = 200;
	position.y = 90;
	maxHp = 1000;
	currentHp = maxHp;
	cooldown = maxCooldown;
	collider = App->collision->AddCollider({ position.x, position.y, 37, 88 }, CENEMY, std::bind(&Enemy::OnCollision, this, std::placeholders::_1, std::placeholders::_2));

	return true;
}

// Unload assets
bool Enemy::CleanUp()
{
	LOG("Unloading enemy");

	App->textures->Unload(graphics);

	RELEASE(Life);
	RELEASE(currentAnimation);
	RELEASE(lastMovementAnimation);
	collider->to_delete = true;
	attackCollider->to_delete = true;
	to_delete = true;


	return true;
}

// Update: draw background
update_status Enemy::Update()
{
	Life->Update();
	if (cooldown <= 0) {
		cooldown = maxCooldown;
		BehaviourTree();
	}
	else {
		cooldown--;
	}

	switch (decision) {
	case (BDGORIGHT) :
		Life->Move(RIGHT);
		break;
	case (BDGOLEFT) :
		Life->Move(LEFT);
		break;
	case (BDGOUP) :
		Life->Move(UP);
		break;
	case (BDGODOWN) :
		Life->Move(DOWN);
		break;
	case (BDATTACK) :
		Life->Attack();
		break;
	case (BDIDLE) :
		Life->Idle();
		break;
	default:
		Life->Idle();
		break;
	}

	if (to_delete == false) {
		App->renderer->AddBlit(graphics, position.x, position.y + App->scene_platform->tremorOffset / 2, &(currentAnimation->GetCurrentFrame()), 1.0f, direction);
		collider->SetPos(position.x, position.y);
	}

	return UPDATE_CONTINUE;
}

void Enemy::OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType) {

	LOG("Collision on enemy");
	switch (otherType) {
	case CPLAYER_ATTACK:
		TakeDamage(10);
	}
}

void Enemy::Die() {
	to_delete = true;
	collider->to_delete = true;
	attackCollider->to_delete = true;
}

void Enemy::BehaviourTree() {
	if (this->position.x < App->scene_platform->player->position.x - 50) {
		decision = BDGORIGHT;
	}
	else if (this->position.x > App->scene_platform->player->position.x + 50) {
		decision = BDGOLEFT;
	}
	else if (this->position.y < App->scene_platform->player->position.y - 10) {
		decision = BDGODOWN;
	}
	else if (this->position.y > App->scene_platform->player->position.y + 10) {
		decision = BDGOUP;
	}
	else if ((abs(this->position.x - App->scene_platform->player->position.x) <= 50)
		&& (abs(this->position.y - App->scene_platform->player->position.y) <= 20)) {
		if (this->position.x < App->scene_platform->player->position.x) {
			direction = true;
		}
		else if (this->position.x > App->scene_platform->player->position.x) {
			direction = false;
		}
		int chance = rand() % 2;
		if (chance == 0) {
			decision = BDATTACK;
		}
		else {
			decision = static_cast<BehaviourDecision>(rand() % 5);
		}
	}
	else {
		decision = BDIDLE;
	}
}