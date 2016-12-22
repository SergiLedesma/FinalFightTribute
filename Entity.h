#ifndef __Entity_H__
#define __Entity_H__

#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

enum EntityType {
	PLAYER,
	ENEMY,
	DESTRUCTIBLE,
	WEAPON,
	FOOD,
	SCORE,
	PARTICLE
};

class Entity
{
public:
	Entity();
	virtual ~Entity();
	bool Start();
	update_status Update();
	void OnCollision();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	Collider* collider = nullptr;
	iPoint position;
	bool destroyed = false;
	bool direction = true; // true = right, false = left
};

#endif