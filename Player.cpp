#include "Player.h"
#include <time.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneStage2Platform.h"
#include "SDL\include\SDL_render.h"


Player::Player() {
	LOG("PLAYER SPAWNED");

	Life = new AnimationStateMachine(this);

	// idle animation
	idle.frames.push_back(FrameInfo({ 7, 7, 37, 88 }));
	attack1.loop = false;
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
}

Player::~Player()
{
}

// Load assets
bool Player::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ff/Sprites/Cody1.png");

	destroyed = false;
	position.x = 110;
	position.y = 80;
	weaponOffset = 25;
	collider = App->collision->AddCollider({ position.x, position.y, 37, 88 }, CPLAYER, std::bind(&Player::OnCollision, this));

	return true;
}

// Unload assets
bool Player::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status Player::Update()
{
	Life->Update();

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
	{
		App->scene_platform->playTrainAnim = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		Life->Move(RIGHT);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		Life->Move(LEFT);
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		Life->Move(UP);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		Life->Move(DOWN);
	}

	/*
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		attack1.Reset();
		currentAnimation = &attack1;
		blockAnimations = true;
	}

	if (blockAnimations) {
		if (attackDelay <= 0) {
			blockAnimations = false;
			attackDelay = 20;
		}
		attackDelay--;
	}

	if (!blockAnimations) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= speed;
			direction = false;
			if (currentAnimation != &left)
			{
				left.Reset();
				currentAnimation = &left;
				lastMovementAnimation = currentAnimation;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed;
			direction = true;
			if (currentAnimation != &right)
			{
				right.Reset();
				currentAnimation = &right;
				lastMovementAnimation = currentAnimation;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += speed;
			if (lastMovementAnimation != nullptr) {
				currentAnimation = lastMovementAnimation;
			}
			else {
				right.Reset();
				currentAnimation = &right;
				lastMovementAnimation = currentAnimation;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= speed;
			if (lastMovementAnimation != nullptr) {
				currentAnimation = lastMovementAnimation;
			}
			else {
				right.Reset();
				currentAnimation = &right;
				lastMovementAnimation = currentAnimation;
			}
		}


		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			//App->particles->AddParticle(App->particles->laser, position.x, position.y);
		}
	}
	*/

	if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_F) == KEY_IDLE)
		|| (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT
			&& App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		|| (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT
			&& App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)) {
		Life->Idle();
	}

	// Draw everything --------------------------------------
	if (destroyed == false) {
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

void Player::OnCollision() {

	LOG("Collision on player");
	/*
	int xOffset = 0;
	int yOffset = 0;
	int offsetRange = 20;

	App->particles->AddParticle(App->particles->explosion, position.x, position.y);

	srand(time(NULL));

	for (int i = 0; i < 4; i++) {
		xOffset = rand() % offsetRange - offsetRange;
		yOffset = rand() % offsetRange - offsetRange;
		App->particles->AddParticle(App->particles->explosion, position.x + xOffset, position.y + yOffset);
	}
	destroyed = true;
	collider->to_delete = true;
	*/
}