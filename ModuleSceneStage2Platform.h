#ifndef __MODULESCENESTAGE2PLATFORM_H__
#define __MODULESCENESTAGE2PLATFORM_H__

#include "Module.h"

struct SDL_Texture;
struct FrameInfo;
class Barrel;

class ModuleSceneStage2Platform : public Module
{
public:
	ModuleSceneStage2Platform(bool active = true);
	~ModuleSceneStage2Platform();

	bool Start();
	bool CleanUp();
	update_status Update();
	bool ChangeTrainPosition(int trainSpeed);

public:

	SDL_Texture* graphics = nullptr;
	FrameInfo background;
	FrameInfo train;
	FrameInfo train2;

	bool playTrainAnim = false;
	int tremorOffset = NULL;

private:
	int tremorSpan = 5;
	int trainSpeed = 5;
	int trainSpeedDecay = 330;
	int baseTrainSpeedDecay = 330;
	int trainCurrentPosition = 1000;
	int trainEndPosition = NULL;
	Barrel *  dest;
};

#endif // __MODULESCENESTAGE2PLATFORM_H__