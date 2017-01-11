#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;
class Timer;

// Game modules ---
class ModulePlayer;
class ModuleScenePreIntro;
class ModuleSceneIntro;
class ModuleSceneStage2Platform;
class ModuleSceneEnding;
class ModuleSceneGameOver;
class EntityManager;
class FxLibrary;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleCollision* collision = nullptr;
	Timer* timer = nullptr;

	// Game modules ---
	ModuleScenePreIntro* scene_preintro = nullptr;
	ModuleSceneIntro* scene_intro = nullptr;
	ModuleSceneStage2Platform* scene_platform = nullptr;
	ModuleSceneEnding* scene_ending = nullptr;
	ModuleSceneGameOver* scene_over = nullptr;
	EntityManager* manager = nullptr;
	FxLibrary* fxlib = nullptr;

private:

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_H__