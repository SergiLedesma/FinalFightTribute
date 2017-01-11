#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

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
class ModuleParticles;
class Timer;

// Game modules ---
class ModulePlayer;
class ModuleScenePreIntro;
class ModuleSceneIntro;
class ModuleSceneStage2Platform;
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
	ModuleParticles* particles = nullptr;
	Timer* timer = nullptr;

	// Game modules ---
	ModuleScenePreIntro* scene_preintro = nullptr;
	ModuleSceneIntro* scene_intro = nullptr;
	ModuleSceneStage2Platform* scene_platform = nullptr;
	EntityManager* manager = nullptr;
	FxLibrary* fxlib = nullptr;

private:

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__