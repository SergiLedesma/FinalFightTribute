#include "TrainTrigger.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "EntityManager.h"
#include "ModuleSceneStage2Platform.h"


TrainTrigger::TrainTrigger()
{
}


TrainTrigger::~TrainTrigger()
{
}

void TrainTrigger::Shot() {
	App->scene_platform->playTrainAnim = true;
	App->audio->PlayFx(App->scene_platform->trainArrival);
}