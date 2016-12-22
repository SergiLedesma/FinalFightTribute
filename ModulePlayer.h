#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	void OnCollision();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* currentAnimation = nullptr;
	Animation* lastMovementAnimation = nullptr;
	Collider* collider = nullptr;
	Animation idle;
	Animation right;
	Animation left;
	Animation attack1;
	bool blockAnimations = false;
	iPoint position;
	bool destroyed = false;
	bool direction = true; // true = right, false = left
	int weaponOffset;

private: 
	int attackDelay = 20;
};

#endif