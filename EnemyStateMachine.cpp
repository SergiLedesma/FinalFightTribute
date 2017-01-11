#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Enemy.h"
#include "ModuleSceneStage2Platform.h"
#include "EnemyStateMachine.h"


EnemyStateMachine::~EnemyStateMachine()
{
	RELEASE(enemy);
	RELEASE(data);
}

//-----------------------------------------------------------------------------------------
// Update of the StateMachine. 
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::Update()
{
	StateMachine::Update();
}


//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::Move(MOVEMENTKEY direction)
{
	data = new EnemyEventData(direction);
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)			// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(ST_MOVING)				// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_MOVING)				// ST_MOVING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK
	END_TRANSITION_MAP(data)
}

//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::Attack()
{
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)			// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(ST_ATTACK)				// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_ATTACK)				// ST_MOVING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK
	END_TRANSITION_MAP(NULL)
}

void EnemyStateMachine::Idle()
{
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_MOVING
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_ATTACK
	END_TRANSITION_MAP(NULL)
}


//-----------------------------------------------------------------------------------------
// Converts a State type to a string
//-----------------------------------------------------------------------------------------
const char * EnemyStateMachine::StateToStr(State state)
{
	const char *paszStates[] = {
#define ENEMY_STATE(_state, _func) #_state,
#include "EnemyState.h"
#undef ENEMY_STATE
	};
	return paszStates[state];
}

//-----------------------------------------------------------------------------------------
// Undefined State
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::OnEnter_Undefined(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Undefined. PrevState: %s", StateToStr(PrevState), "\n");
	OnEvent(ST_IDLE, NULL);
}

void EnemyStateMachine::OnUpdate_Undefined()
{
	// LOG("OnUpdate_Undefined\n");
	OnEvent(ST_IDLE, NULL);
}

void EnemyStateMachine::OnExit_Undefined(State NextState)
{
	// LOG("OnExit_Undefined. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Idle State
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::OnEnter_Idle(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Idle. PrevState: %s", StateToStr(PrevState), "\n");
	enemy->currentAnimation = &enemy->idle;
}

void EnemyStateMachine::OnUpdate_Idle()
{
	// LOG("OnUpdate_Idle\n");
}

void EnemyStateMachine::OnExit_Idle(State NextState)
{
	// LOG("OnExit_Idle. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Moving State
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::OnEnter_Moving(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Moving. PrevState: %s", StateToStr(PrevState), "\n");
	switch (((EnemyEventData*)pData)->direction) {
	case RIGHT:
		enemy->position.x += enemy->speed;
		enemy->direction = true;
		if (enemy->currentAnimation != &enemy->right)
		{
			enemy->right.Reset();
			enemy->currentAnimation = &enemy->right;
			enemy->lastMovementAnimation = enemy->currentAnimation;
		}
		break;
	case LEFT:
		if (enemy->position.x - enemy->speed > -App->renderer->camera.x / SCREEN_SIZE) {
			enemy->position.x -= enemy->speed;
		}
		enemy->direction = false;
		if (enemy->currentAnimation != &enemy->left)
		{
			enemy->left.Reset();
			enemy->currentAnimation = &enemy->left;
			enemy->lastMovementAnimation = enemy->currentAnimation;
		}
		break;
	case UP:
		if (enemy->position.y - enemy->speed > -App->renderer->camera.y / SCREEN_SIZE + App->scene_platform->walkableSpaceY) {
			enemy->position.y -= enemy->speed;
		}
		if ((enemy->lastMovementAnimation == &enemy->left) || (enemy->lastMovementAnimation == &enemy->right)) {
			enemy->currentAnimation = enemy->lastMovementAnimation;
		}
		else {
			enemy->right.Reset();
			enemy->currentAnimation = &enemy->right;
			enemy->lastMovementAnimation = enemy->currentAnimation;
		}
		break;
	case DOWN:
		if (enemy->position.y + 90 + enemy->speed < (-App->renderer->camera.y + App->renderer->camera.h) / SCREEN_SIZE) {
			enemy->position.y += enemy->speed;
		}
		if ((enemy->lastMovementAnimation == &enemy->left) || (enemy->lastMovementAnimation == &enemy->right)) {
			enemy->currentAnimation = enemy->lastMovementAnimation;
		}
		else {
			enemy->right.Reset();
			enemy->currentAnimation = &enemy->right;
			enemy->lastMovementAnimation = enemy->currentAnimation;
		}
		break;
	}
}

void EnemyStateMachine::OnUpdate_Moving()
{
	
}

void EnemyStateMachine::OnExit_Moving(State NextState)
{
	// LOG("OnExit_Moving. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Attack State
//-----------------------------------------------------------------------------------------
void EnemyStateMachine::OnEnter_Attack(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Attack. PrevState: %s", StateToStr(PrevState), "\n");
	enemy->finishedAnimation = false;
	enemy->animationCountdown = 18;
	enemy->attack.Reset();
	enemy->currentAnimation = &enemy->attack;
	enemy->attackCollider = App->collision->AddCollider({ enemy->position.x, enemy->position.y, 35, 60 }, CENEMY_ATTACK, std::bind(&Enemy::OnCollision, enemy, std::placeholders::_1, std::placeholders::_2));
}

void EnemyStateMachine::OnUpdate_Attack()
{
	// LOG("OnUpdate_Attack\n");
	if (enemy->animationCountdown <= 0) {
		enemy->finishedAnimation = true;
	}
	else {
		enemy->animationCountdown -= 1;
	}
	int colliderX = NULL;
	if (enemy->direction) {
		colliderX = enemy->position.x + enemy->collider->rect.w;
	}
	else {
		colliderX = enemy->position.x - enemy->attackCollider->rect.w;
	}
	enemy->attackCollider->SetPos(colliderX, enemy->position.y);
	if (enemy->finishedAnimation) {
		Idle();
	}
}

void EnemyStateMachine::OnExit_Attack(State NextState)
{
	// LOG("OnExit_Attack. NextState: %s", StateToStr(NextState), "\n");
	enemy->attackCollider->to_delete = true;
}