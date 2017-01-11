#include "EndingTrigger.h"
#include <time.h>
#include "Application.h"
#include "EntityManager.h"
#include "ModuleSceneStage2Platform.h"



EndingTrigger::EndingTrigger()
{
}


EndingTrigger::~EndingTrigger()
{
}


void EndingTrigger::Shot() {
	App->scene_platform->ending = true;
}