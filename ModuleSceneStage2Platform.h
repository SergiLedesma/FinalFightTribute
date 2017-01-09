#ifndef __MODULESCENESTAGE2PLATFORM_H__
#define __MODULESCENESTAGE2PLATFORM_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
class Barrel;
class Player;

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
	int walkableSpaceY = 55;

	bool playTrainAnim = false;
	int tremorOffset = NULL;

	Player* player = nullptr;

private:
	int tremorSpan = 5;
	int trainSpeed = 5;
	int trainSpeedDecay = 330;
	int baseTrainSpeedDecay = 330;
	int trainCurrentPosition = 1000;
	int trainEndPosition = NULL;
	Barrel *  barrel1 = nullptr;
	Barrel *  barrel2 = nullptr;
};

#endif // __MODULESCENESTAGE2PLATFORM_H__