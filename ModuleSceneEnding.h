#ifndef __MODULESCENEENDING_H__
#define __MODULESCENEENDING_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSceneEnding : public Module
{
public:
	ModuleSceneEnding(bool active = true);
	~ModuleSceneEnding();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* background = nullptr;
};

#endif // __MODULESCENEINTRO_H__