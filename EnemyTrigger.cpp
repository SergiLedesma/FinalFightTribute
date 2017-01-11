#include <time.h>
#include "EnemyTrigger.h"
#include "Application.h"
#include "EntityManager.h"
#include "ModuleSceneStage2Platform.h"



EnemyTrigger::EnemyTrigger()
{
}


EnemyTrigger::~EnemyTrigger()
{
}

void EnemyTrigger::Shot() {
	int offset = rand() % 40 + 25;
	App->scene_platform->SpawnEnemy(position.x + SCREEN_WIDTH / 2 + offset, position.y + SCREEN_HEIGHT/2 + offset);
}