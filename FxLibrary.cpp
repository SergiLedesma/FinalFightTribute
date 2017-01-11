#include "FxLibrary.h"
#include "Application.h"
#include "ModuleAudio.h"


FxLibrary::FxLibrary(bool active) : Module(active)
{
}


FxLibrary::~FxLibrary()
{
}

bool FxLibrary::Start()
{
	if (fxPunch1 == 0) {
		fxPunch1 = App->audio->LoadFx("ff/Audio/sounds/punch001.wav");
	}
	if (fxPunch2 == 0) {
		fxPunch2 = App->audio->LoadFx("ff/Audio/sounds/punch002.wav");
	}
	if (fxPunch3 == 0) {
		fxPunch3 = App->audio->LoadFx("ff/Audio/sounds/punch003.wav");
	}
	if (fxPunch4 == 0) {
		fxPunch4 = App->audio->LoadFx("ff/Audio/sounds/punch004.wav");
	}
	return true;
}