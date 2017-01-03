#pragma once
#include "Creature.h"
#include "Animation.h"
#include "Point.h"
#include "AnimationStateMachine.h"

struct SDL_Texture;
struct Collider;

class Player :
	public Creature
{
public:
	Player();
	~Player();

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
	int speed = 1;

private:
	int attackDelay = 20;
	AnimationStateMachine* Life;
};

