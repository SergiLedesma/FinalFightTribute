#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
	defaultSection = new FrameInfo({ 0, 0, 0, 0 });
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// Sort queue of elements to blit
	blitList.sort([](BlitInfo const a, BlitInfo const b) { return a.z < b.z; });

	// Blit all elements in queue
	for (std::list<BlitInfo>::iterator it = blitList.begin(); it != blitList.end(); ++it)
	{
		Blit(it->texture, it->x, it->y, it->section, it->speed, it->direction);
	}
	blitList.clear();
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	RELEASE(defaultSection);

	//Destroy window
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Add elements to queue list
bool ModuleRender::AddBlit(SDL_Texture* texture, int x, int y, const FrameInfo* section, float speed, bool direction, bool isBackground)
{
	BlitInfo currentBlit = BlitInfo();
	currentBlit.texture = texture;
	currentBlit.x = x;
	currentBlit.y = y;
	currentBlit.speed = speed;
	currentBlit.direction = direction;
	if (section == nullptr) {
		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		defaultSection->frame.w = w;
		defaultSection->frame.h = h;
		section = defaultSection;
	}
	currentBlit.section = section;
	if (!isBackground) {
		currentBlit.z = y + section->frame.h;
	}
	else {
		currentBlit.z = -1000;
	}


	blitList.push_back(currentBlit);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const FrameInfo* section, float speed, bool direction)
{
	bool ret = true;
	SDL_Rect rect;

	if (section != nullptr)
	{
		rect.w = section->frame.w;
		rect.h = section->frame.h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;
	if (section != nullptr) {
		rect.y = (int)(camera.y * speed) + (y + section->yOffset) * SCREEN_SIZE;
	}
	if (direction) {
		rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
		if (SDL_RenderCopy(renderer, texture, &section->frame, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	else {
		rect.x = (int)(camera.x * speed) + (x - section->xOffset) * SCREEN_SIZE;
		if (SDL_RenderCopyEx(renderer, texture, &section->frame, &rect, NULL, nullptr, SDL_FLIP_HORIZONTAL) != 0) {
			LOG("Cannot blit to screen. SDL_RenderCopyEx error: %s", SDL_GetError());
			ret = false;
		}
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::DebugCamera()
{
	int speed = 5;
	/*
	if (App->input->GetKey(CAMERAUP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if (App->input->GetKey(CAMERADOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;
		*/

	if (App->input->GetKey(CAMERALEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if (App->input->GetKey(CAMERARIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;
}
