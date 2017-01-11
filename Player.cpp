#include "Player.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneStage2Platform.h"
#include "FxLibrary.h"
#include "Timer.h"
#include "SDL\include\SDL_render.h"


#include <time.h>


Player::Player() {
	LOG("PLAYER SPAWNED");

	Life = new AnimationStateMachine(this);

	// idle animation
	idle.frames.push_back(FrameInfo({ 7, 7, 37, 88 }));
	idle.loop = false;
	idle.speed = 0.2f;

	// move right
	right.frames.push_back(FrameInfo({ 14, 102, 24, 87 }));
	right.frames.push_back(FrameInfo({ 53, 101, 45, 87 }));
	right.frames.push_back(FrameInfo({ 114, 101, 37, 87 }));
	right.frames.push_back(FrameInfo({ 164, 100, 26, 88 }));
	right.frames.push_back(FrameInfo({ 213, 101, 45, 87 }));
	right.frames.push_back(FrameInfo({ 267, 101, 36, 86 }));
	right.loop = true;
	right.speed = 0.1f;

	// move left
	left = right;
	left.loop = true;
	left.speed = 0.1f;

	// attack1
	attack1.frames.push_back(FrameInfo({ 12, 440, 45, 85 }, 6, 3));
	attack1.frames.push_back(FrameInfo({ 66, 440, 62, 85 }, 23, 3));
	attack1.frames.push_back(FrameInfo({ 12, 440, 45, 85 }, 6, 3));
	attack1.loop = false;
	attack1.speed = 0.2f;

	// attack2
	attack2.frames.push_back(FrameInfo({ 136, 449, 47, 76 }, 10, 12));
	attack2.frames.push_back(FrameInfo({ 197, 454, 75, 71 }, 40, 15));
	attack2.loop = false;
	attack2.speed = 0.2f;

	// attack3
	attack3.frames.push_back(FrameInfo({ 277, 458, 56, 67 }, 25, 18));
	attack3.frames.push_back(FrameInfo({ 349, 453, 58, 73 }, 30, 15));
	attack3.frames.push_back(FrameInfo({ 410, 441, 58, 85 }, 22, -2));
	attack3.frames.push_back(FrameInfo({ 476, 423, 40, 104 }, 10, -20));
	attack3.loop = false;
	attack3.speed = 0.2f;

	// jumpUp
	jumpUp.frames.push_back(FrameInfo({ 18, 239, 37, 79 }, 0, 10));
	jumpUp.frames.push_back(FrameInfo({ 75, 204, 30, 104 }, 0, -10));
	jumpUp.frames.push_back(FrameInfo({ 75, 204, 30, 104 }, 0, -10));
	jumpUp.frames.push_back(FrameInfo({ 75, 204, 30, 104 }, 0, -10));
	jumpUp.frames.push_back(FrameInfo({ 123, 219, 38, 72 }, 0, 0));
	jumpUp.frames.push_back(FrameInfo({ 123, 219, 38, 72 }, 0, 0));
	jumpUp.frames.push_back(FrameInfo({ 75, 204, 30, 104 }, 0, -10));
	jumpUp.frames.push_back(FrameInfo({ 75, 204, 30, 104 }, 0, -10));
	jumpUp.frames.push_back(FrameInfo({ 18, 239, 37, 79 }, 0, 10));
	jumpUp.loop = false;
	jumpUp.speed = 0.2f;

	// jumpForward
	jumpForward.frames.push_back(FrameInfo({ 18, 239, 37, 79 }, 0, 10));
	jumpForward.frames.push_back(FrameInfo({ 75, 204, 30, 104 }, 0, -10));
	jumpForward.frames.push_back(FrameInfo({ 123, 219, 38, 72 }, 0, 0));
	jumpForward.frames.push_back(FrameInfo({ 243, 242, 52, 48 }, 0, 0));
	jumpForward.frames.push_back(FrameInfo({ 306, 239, 48, 52 }, 0, 0));
	jumpForward.frames.push_back(FrameInfo({ 367, 240, 52, 48 }, 0, 0));
	jumpForward.frames.push_back(FrameInfo({ 434, 232, 48, 52 }, 0, 0));
	jumpForward.frames.push_back(FrameInfo({ 18, 239, 37, 79 }, 0, 10));
	jumpForward.loop = false;
	jumpForward.speed = 0.2f;

	// jumpUpKick
	jumpUpKick.frames.push_back(FrameInfo({ 19, 541, 38, 82 }, 0, 0));
	jumpUpKick.frames.push_back(FrameInfo({ 68, 541, 46, 80 }, 0, 0));
	jumpUpKick.loop = false;
	jumpUpKick.speed = 0.2f;

	// jumpForwardKick
	jumpForwardKick.frames.push_back(FrameInfo({ 17, 329, 38, 80 }, 0, 0));
	jumpForwardKick.frames.push_back(FrameInfo({ 67, 353, 79, 56 }, 50, 10));
	jumpForwardKick.loop = false;
	jumpForwardKick.speed = 0.2f;
}

Player::~Player()
{
}

// Load assets
bool Player::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ff/Sprites/Cody1.png");

	position.x = 110;
	position.y = 80;
	maxHp = 200;
	currentHp = maxHp;
	collider = App->collision->AddCollider({ position.x, position.y, 37, 88 }, CPLAYER, std::bind(&Player::OnCollision, this, std::placeholders::_1, std::placeholders::_2));

	return true;
}

// Unload assets
bool Player::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	to_delete = true;
	if (collider != nullptr) {
		collider->to_delete = true;
	}
	if (attackCollider != nullptr) {
		attackCollider->to_delete = true;
	}
	RELEASE(Life);

	return true;
}

// Update: draw background
update_status Player::Update()
{
	Life->Update();

	LOG("%d", currentHp);

	if (App->input->GetKey(DEBUG) == KEY_DOWN) {
		if (debug) {
			App->renderer->camera.x = -position.x * SCREEN_SIZE + App->renderer->camera.w * 1 / 3;
		}
		debug = !debug;
	}

	if ((App->input->GetKey(JUMP) == KEY_DOWN) && (App->input->GetKey(GORIGHT) == KEY_REPEAT))
	{
		Life->Jump(RIGHT);
	}
	if ((App->input->GetKey(JUMP) == KEY_DOWN) && (App->input->GetKey(GOLEFT) == KEY_REPEAT))
	{
		Life->Jump(LEFT);
	}

	if (App->input->GetKey(GORIGHT) == KEY_REPEAT)
	{
		Life->Move(RIGHT);
	}

	if (App->input->GetKey(GOLEFT) == KEY_REPEAT)
	{
		Life->Move(LEFT);
	}

	if (App->input->GetKey(GOUP) == KEY_REPEAT)
	{
		Life->Move(UP);
	}

	if (App->input->GetKey(GODOWN) == KEY_REPEAT)
	{
		Life->Move(DOWN);
	}

	if (App->input->GetKey(ATTACK) == KEY_DOWN)
	{
		Life->Attack();
	}

	if (App->input->GetKey(JUMP) == KEY_DOWN)
	{
		Life->Jump(NONE);
	}

	if (App->input->GetKey(PAUSE) == KEY_DOWN)
	{
		if (App->timer->IsPaused()) {
			App->timer->Unpause();
		}
		else {
			App->timer->Pause();
		}
	}

	if (debug) {
		App->collision->DebugDraw();
		App->renderer->DebugCamera();
	}
	else {
		if (!lockCamera && (position.x > (-App->renderer->camera.x + App->renderer->camera.w * 1 / 3) / SCREEN_SIZE)) {
			App->renderer->camera.x = - position.x * SCREEN_SIZE + App->renderer->camera.w * 1 / 3;
		}
	}

	if (to_delete == false) {
		App->renderer->AddBlit(graphics, position.x, position.y + App->scene_platform->tremorOffset / 2, &(currentAnimation->GetCurrentFrame()), 1.0f, direction);
		collider->SetPos(position.x, position.y);
	}
	else {
		if (App->fade->isFading() == false) {
			App->fade->FadeToBlack((Module*)App->scene_intro, App->fade->getCurrentModule(), 3.0f);
		}
	}

	return UPDATE_CONTINUE;
}

void Player::OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType) {

	switch (otherType) {
	case CENEMY_ATTACK:
		if (!debug) {
		TakeDamage(1);
		}
		int punchSound = rand() % 4;
		switch (punchSound) {
		case 0:
			App->audio->PlayFx(App->fxlib->fxPunch1);
			break;
		case 1:
			App->audio->PlayFx(App->fxlib->fxPunch2);
			break;
		case 2:
			App->audio->PlayFx(App->fxlib->fxPunch3);
			break;
		case 3:
			App->audio->PlayFx(App->fxlib->fxPunch4);
			break;
		}
	}
}

void Player::Die() {
	to_delete = true;
}