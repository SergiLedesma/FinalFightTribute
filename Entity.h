#ifndef __Entity_H__
#define __Entity_H__

#include "Globals.h"
#include "Point.h"
#include "Animation.h"

struct SDL_Texture;
struct FrameInfo;
struct Collider;

enum EntityType {
	PLAYER,
	ENEMY,
	BARREL,
	TRAINTRIGGER,
	ENEMYTRIGGER,
	ENDINGTRIGGER
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

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
	Collider* collider = nullptr;
	FrameInfo rect;
	iPoint position;
	int z = NULL;
	bool to_delete = false;
	bool direction = true; // true = right, false = left

protected:
	int lifeSpan = NULL;
};

#endif