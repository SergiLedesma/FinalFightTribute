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
	Animation attack1;
	Animation attack2;
	Animation attack3;
	Animation jumpUp;
	Animation jumpForward;
	Animation jumpUpKick;
	Animation jumpForwardKick;
	bool finishedAnimation = false;
	int animationCountdown = NULL;
	iPoint position;
	bool destroyed = false;
	bool direction = true; // true = right, false = left
	int weaponOffset;
	int speed = 1;

private:
	int attackDelay = 20;
	AnimationStateMachine* Life;
};

