#ifndef __MODULESCENEGAMEOVER_H__
#define __MODULESCENEGAMEOVER_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSceneGameOver : public Module
{
public:
	ModuleSceneGameOver(bool active = true);
	~ModuleSceneGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* background = nullptr;
};

#endif // __MODULESCENEGAMEOVER_H__