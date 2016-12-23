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
	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}
	
	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}
	
	virtual bool CleanUp()
	{
		return true;
	}

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect rect;
	Collider* collider = nullptr;
	iPoint position;
	int z;
	bool destroyed = false;
	bool direction = true; // true = right, false = left
};

#endif