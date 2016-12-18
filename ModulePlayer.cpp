#include <time.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleSceneStage2Platform.h"
#include "SDL\include\SDL_render.h"

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	// idle animation
	idle.frames.push_back({7, 7, 37, 88});

	// move right
	right.frames.push_back({ 14, 102, 24, 87 });
	right.frames.push_back({ 53, 101, 45, 87 });
	right.frames.push_back({ 114, 101, 37, 87 });
	right.frames.push_back({ 164, 100, 26, 88 });
	right.frames.push_back({ 213, 101, 45, 87 });
	right.frames.push_back({ 267, 101, 36, 86 });
	right.loop = true;
	right.speed = 0.1f;
	
	// move left
	/*SDL_RenderCopyEx(App->renderer->renderer,
		graphics,
		&a,
		&b,
		NULL,
		NULL,
		SDL_FLIP_HORIZONTAL);*/
	left.frames.push_back({33, 1, 32, 14});
	left.frames.push_back({0, 1, 32, 14});
	left.loop = false;
	left.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ff/Sprites/Cody1NoBackground.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;
	weaponOffset = 25;
	collider = App->collision->AddCollider({ position.x, position.y, 32, 12 }, PLAYER, std::bind(&ModulePlayer::OnCollision, this));

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
	{
		App->scene_platform->playTrainAnim = true;
	}
	

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		direction = false;
		position.x -= speed;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
		direction = true;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//App->particles->AddParticle(App->particles->laser, position.x, position.y);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		current_animation = &idle;
	}

	// Draw everything --------------------------------------
	if (destroyed == false) {
		App->renderer->Blit(graphics, position.x, position.y + App->scene_platform->tremorOffset/2, &(current_animation->GetCurrentFrame()));
		collider->SetPos(position.x, position.y);
	}
	else {
		if (App->fade->isFading() == false) {
			App->fade->FadeToBlack((Module*)App->scene_intro, App->fade->getCurrentModule(), 3.0f);
		}
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision() {

	LOG("Collision on player");

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
}