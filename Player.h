#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <map>
#include "Creature.h"
#include "Animation.h"
#include "Point.h"
#include "AnimationStateMachine.h"
#include "ModuleCollision.h"

struct SDL_Texture;
struct Collider;

class Player :
	public Creature
{
public:
	Player();
	~Player();

	bool Start();
	bool CleanUp();
	update_status Update();
	void OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType);
	void Die();
	bool GetDebugMode() { return debug; };

public:
	Animation attack1;
	Animation attack2;
	Animation attack3;
	Animation jumpUp;
	Animation jumpForward;
	Animation jumpUpKick;
	Animation jumpForwardKick;
	bool direction = true; // true = right, false = left
	int speed = 1;
	int capsuleW = 37;
	int capsuleH = 87;
	bool lockCamera = false;

private:
	int attackDelay = 20;
	AnimationStateMachine* Life;
	bool debug = false;
};

#endif // __PLAYER_H__