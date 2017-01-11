#ifndef __MODULESCENEPREINTRO_H__
#define __MODULESCENEPREINTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
class FrameInfo;

class ModuleScenePreIntro : public Module
{
public:
	ModuleScenePreIntro(bool active = true);
	~ModuleScenePreIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;

private:
	int countdown = 180;
};

#endif // __MODULESCENEPREINTRO_H__