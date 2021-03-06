#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "Timer.h"

#include "ModuleScenePreIntro.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneStage2Platform.h"
#include "ModuleSceneEnding.h"
#include "ModuleSceneGameOver.h"
#include "EntityManager.h"
#include "FxLibrary.h"
#include "Application.h"

using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(fxlib = new FxLibrary());
	modules.push_back(audio = new ModuleAudio());

	// Game Modules
	modules.push_back(scene_preintro = new ModuleScenePreIntro(false));
	modules.push_back(scene_intro = new ModuleSceneIntro(false));
	modules.push_back(scene_platform = new ModuleSceneStage2Platform(false));
	modules.push_back(scene_ending = new ModuleSceneEnding(false));
	modules.push_back(scene_over = new ModuleSceneGameOver(false));
	modules.push_back(manager = new EntityManager(true));
	
	// Modules to draw on top of game logic
	modules.push_back(timer = new Timer());
	modules.push_back(collision = new ModuleCollision());
	modules.push_back(fade = new ModuleFadeToBlack());

}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not enabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}
	timer->Start();

	// Start the first scene --
	fade->FadeToBlack(scene_preintro, nullptr, 3.0f);

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

