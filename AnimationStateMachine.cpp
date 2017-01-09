#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Player.h"
#include "ModuleSceneStage2Platform.h"
#include "AnimationStateMachine.h"


AnimationStateMachine::~AnimationStateMachine()
{
	RELEASE(player);
	RELEASE(data);
}

//-----------------------------------------------------------------------------------------
// Update of the StateMachine. 
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::Update()
{
	StateMachine::Update();
}


//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::Move(MOVEMENTKEY direction)
{
	data = new AnimationEventData(direction);
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)			// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(ST_MOVING)				// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_MOVING)				// ST_MOVING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_UP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_UP_KICK
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_FORWARD
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_FORWARD_KICK
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK3
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_GRAB
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_PUNCH
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_THROW
	END_TRANSITION_MAP(data)
}


//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::Jump(MOVEMENTKEY direction)
{
	data = new AnimationEventData(direction);
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)			// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(ST_JUMP_UP)			// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_JUMP_FORWARD)		// ST_MOVING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_UP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_UP_KICK
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_FORWARD
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_FORWARD_KICK
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK3
		TRANSITION_MAP_ENTRY(ST_THROW)				// ST_GRAB
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_PUNCH
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_THROW
	END_TRANSITION_MAP(NULL)
}

//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::Attack()
{
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)			// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(ST_ATTACK1)			// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_ATTACK1)			// ST_MOVING
		TRANSITION_MAP_ENTRY(ST_JUMP_UP_KICK)		// ST_JUMP_UP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_UP_KICK
		TRANSITION_MAP_ENTRY(ST_JUMP_FORWARD_KICK)	// ST_JUMP_FORWARD
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_JUMP_FORWARD_KICK
		TRANSITION_MAP_ENTRY(ST_ATTACK2)			// ST_ATTACK1
		TRANSITION_MAP_ENTRY(ST_ATTACK3)			// ST_ATTACK2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_ATTACK3
		TRANSITION_MAP_ENTRY(ST_PUNCH)				// ST_GRAB
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_PUNCH
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_THROW
	END_TRANSITION_MAP(NULL)
}

void AnimationStateMachine::Idle()
{
	BEGIN_TRANSITION_MAP							// - Current State -
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_UNDEFINED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_MOVING
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_JUMP_UP
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_JUMP_UP_KICK
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_JUMP_FORWARD
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_JUMP_FORWARD_KICK
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_ATTACK1
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_ATTACK2
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_ATTACK3
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_GRAB
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_PUNCH
		TRANSITION_MAP_ENTRY(ST_IDLE)				// ST_THROW
	END_TRANSITION_MAP(NULL)
}


//-----------------------------------------------------------------------------------------
// Converts a State type to a string
//-----------------------------------------------------------------------------------------
const char * AnimationStateMachine::StateToStr(State state)
{
	const char *paszStates[] = {
#define ANIMATION_STATE(_state, _func) #_state,
#include "AnimationState.h"
#undef ANIMATION_STATE
	};
	return paszStates[state];
}

//-----------------------------------------------------------------------------------------
// Undefined State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Undefined(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Undefined. PrevState: %s", StateToStr(PrevState), "\n");
	OnEvent(ST_IDLE, NULL);
}

void AnimationStateMachine::OnUpdate_Undefined()
{
	// LOG("OnUpdate_Undefined\n");
	OnEvent(ST_IDLE, NULL);
}

void AnimationStateMachine::OnExit_Undefined(State NextState)
{
	// LOG("OnExit_Undefined. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Idle State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Idle(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Idle. PrevState: %s", StateToStr(PrevState), "\n");
	player->currentAnimation = &player->idle;
}

void AnimationStateMachine::OnUpdate_Idle()
{
	// LOG("OnUpdate_Idle\n");
}

void AnimationStateMachine::OnExit_Idle(State NextState)
{
	// LOG("OnExit_Idle. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Moving State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Moving(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Moving. PrevState: %s", StateToStr(PrevState), "\n");
	switch (((AnimationEventData*)pData)->direction) {
	case RIGHT:
		if (player->position.x + App->scene_platform->player->capsuleW + player->speed < (- App->renderer->camera.x + App->renderer->camera.w) / SCREEN_SIZE) {
			player->position.x += player->speed;
		}
		player->direction = true;
		if (player->currentAnimation != &player->right)
		{
			player->right.Reset();
			player->currentAnimation = &player->right;
			player->lastMovementAnimation = player->currentAnimation;
		}
		break;
	case LEFT:
		if (player->position.x - player->speed > - App->renderer->camera.x / SCREEN_SIZE) {
			player->position.x -= player->speed;
		}
		player->direction = false;
		if (player->currentAnimation != &player->left)
		{
			player->left.Reset();
			player->currentAnimation = &player->left;
			player->lastMovementAnimation = player->currentAnimation;
		}
		break;
	case UP:
		if (player->position.y - player->speed > - App->renderer->camera.y / SCREEN_SIZE + App->scene_platform->walkableSpaceY) {
			player->position.y -= player->speed;
		}
		if ((player->lastMovementAnimation == &player->left) || (player->lastMovementAnimation == &player->right)) {
			player->currentAnimation = player->lastMovementAnimation;
		}
		else {
			player->right.Reset();
			player->currentAnimation = &player->right;
			player->lastMovementAnimation = player->currentAnimation;
		}
		break;
	case DOWN:
		if (player->position.y + App->scene_platform->player->capsuleH + player->speed < (-App->renderer->camera.y + App->renderer->camera.h) / SCREEN_SIZE) {
			player->position.y += player->speed;
		}
		if ((player->lastMovementAnimation == &player->left) || (player->lastMovementAnimation == &player->right)) {
			player->currentAnimation = player->lastMovementAnimation;
		}
		else {
			player->right.Reset();
			player->currentAnimation = &player->right;
			player->lastMovementAnimation = player->currentAnimation;
		}
		break;
	}
}

void AnimationStateMachine::OnUpdate_Moving()
{
	// LOG("OnUpdate_Moving\n");
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		|| (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT
			&& App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		|| (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT
			&& App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_Moving(State NextState)
{
	// LOG("OnExit_Moving. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// JumpUp State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_JumpUp(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_JumpUp. PrevState: %s", StateToStr(PrevState), "\n");
	playerRealY = player->position.y;
	player->finishedAnimation = false;
	player->animationCountdown = 40;
	if (player->currentAnimation != &player->jumpUp)
	{
		player->jumpUp.Reset();
		player->currentAnimation = &player->jumpUp;
		player->lastMovementAnimation = player->currentAnimation;
	}
}

void AnimationStateMachine::OnUpdate_JumpUp()
{
	// LOG("OnUpdate_JumpUp\n");
	if (player->animationCountdown >= 20) {
		player->position.y -= 3;
	}
	else {
		player->position.y += 3;
	}
	if (player->animationCountdown <= 0) {
		player->position.y = playerRealY;
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_JumpUp(State NextState)
{
	// LOG("OnExit_JumpUp. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// JumpUpKick State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_JumpUpKick(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_JumpUpKick. PrevState: %s", StateToStr(PrevState), "\n");
	if (player->currentAnimation == &player->jumpUp)
	{
		player->jumpUpKick.Reset();
		player->currentAnimation = &player->jumpUpKick;
		player->lastMovementAnimation = player->currentAnimation;
		player->attackCollider = App->collision->AddCollider({ player->position.x, player->position.y, 20, 80 }, CPLAYER_ATTACK, std::bind(&Player::OnCollision, player, std::placeholders::_1));
	}
}

void AnimationStateMachine::OnUpdate_JumpUpKick()
{
	// LOG("OnUpdate_JumpUpKick\n");
	if (player->animationCountdown >= 20) {
		player->position.y -= 3;
	}
	else {
		player->position.y += 3;
	}
	if (player->animationCountdown <= 0) {
		player->position.y = playerRealY;
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	int colliderX = NULL;
	if (player->direction) {
		colliderX = player->position.x + player->collider->rect.w;
	}
	else {
		colliderX = player->position.x - player->attackCollider->rect.w;
	}
	player->attackCollider->SetPos(colliderX, player->position.y);
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_JumpUpKick(State NextState)
{
	// LOG("OnExit_JumpUpKick. NextState: %s", StateToStr(NextState), "\n");
	player->attackCollider->to_delete = true;
}

//-----------------------------------------------------------------------------------------
// JumpForward State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_JumpForward(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_JumpForward. PrevState: %s", StateToStr(PrevState), "\n");
	playerRealY = player->position.y;
	player->finishedAnimation = false;
	player->animationCountdown = 40;
	if (player->currentAnimation != &player->jumpForward)
	{
		player->jumpForward.Reset();
		player->currentAnimation = &player->jumpForward;
		player->lastMovementAnimation = player->currentAnimation;
	}
}

void AnimationStateMachine::OnUpdate_JumpForward()
{
	// LOG("OnUpdate_JumpForward\n");
	if (player->animationCountdown >= 20) {
		player->position.y -= 3;
	}
	else {
		player->position.y += 3;
	}
	if (player->direction) {
		if (player->position.x + App->scene_platform->player->capsuleW + player->speed < (-App->renderer->camera.x + App->renderer->camera.w) / SCREEN_SIZE) {
			player->position.x += player->speed * 2;
		}
	}
	else {
		if (player->position.x - player->speed > -App->renderer->camera.x / SCREEN_SIZE) {
			player->position.x -= player->speed * 2;
		}
	}
	if (player->animationCountdown <= 0) {
		player->position.y = playerRealY;
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_JumpForward(State NextState)
{
	// LOG("OnExit_JumpForward. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// JumpForwardKick State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_JumpForwardKick(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_JumpForwardKick. PrevState: %s", StateToStr(PrevState), "\n");
	if (player->currentAnimation == &player->jumpForward)
	{
		player->jumpForwardKick.Reset();
		player->currentAnimation = &player->jumpForwardKick;
		player->lastMovementAnimation = player->currentAnimation;
		player->attackCollider = App->collision->AddCollider({ player->position.x, player->position.y, 40, 80 }, CPLAYER_ATTACK, std::bind(&Player::OnCollision, player, std::placeholders::_1));
	}
}

void AnimationStateMachine::OnUpdate_JumpForwardKick()
{
	// LOG("OnUpdate_JumpForwardKick\n");
	if (player->animationCountdown >= 20) {
		player->position.y -= 3;
	}
	else {
		player->position.y += 3;
	}
	if (player->direction) {
		player->position.x += 2;
	}
	else {
		player->position.x -= 2;
	}
	if (player->animationCountdown <= 0) {
		player->position.y = playerRealY;
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	int colliderX = NULL;
	if (player->direction) {
		colliderX = player->position.x + player->collider->rect.w;
	}
	else {
		colliderX = player->position.x - player->attackCollider->rect.w;
	}
	player->attackCollider->SetPos(colliderX, player->position.y);
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_JumpForwardKick(State NextState)
{
	// LOG("OnExit_JumpForwardKick. NextState: %s", StateToStr(NextState), "\n");
	player->attackCollider->to_delete = true;
}

//-----------------------------------------------------------------------------------------
// Attack1 State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Attack1(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Attack1. PrevState: %s", StateToStr(PrevState), "\n");
	player->finishedAnimation = false;
	player->animationCountdown = 18;
	player->attack1.Reset();
	player->currentAnimation = &player->attack1;
	player->attackCollider = App->collision->AddCollider({ player->position.x, player->position.y, 35, 60 }, CPLAYER_ATTACK, std::bind(&Player::OnCollision, player, std::placeholders::_1));
}

void AnimationStateMachine::OnUpdate_Attack1()
{
	// LOG("OnUpdate_Attack1\n");
	if (player->animationCountdown <= 0) {
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	int colliderX = NULL;
	if (player->direction) {
		colliderX = player->position.x + player->collider->rect.w;
	}
	else {
		colliderX = player->position.x - player->attackCollider->rect.w;
	}
	player->attackCollider->SetPos(colliderX, player->position.y);
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_Attack1(State NextState)
{
	// LOG("OnExit_Attack1. NextState: %s", StateToStr(NextState), "\n");
	player->attackCollider->to_delete = true;
}

//-----------------------------------------------------------------------------------------
// Attack2 State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Attack2(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Attack2. PrevState: %s", StateToStr(PrevState), "\n");
	player->finishedAnimation = false;
	player->animationCountdown = 20;
	player->attack2.Reset();
	player->currentAnimation = &player->attack2;
	player->attackCollider = App->collision->AddCollider({ player->position.x, player->position.y, 35, 60 }, CPLAYER_ATTACK, std::bind(&Player::OnCollision, player, std::placeholders::_1));
}

void AnimationStateMachine::OnUpdate_Attack2()
{
	// LOG("OnUpdate_Attack2\n");
	if (player->animationCountdown <= 0) {
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	int colliderX = NULL;
	if (player->direction) {
		colliderX = player->position.x + player->collider->rect.w;
	}
	else {
		colliderX = player->position.x - player->attackCollider->rect.w;
	}
	player->attackCollider->SetPos(colliderX, player->position.y);
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_Attack2(State NextState)
{
	// LOG("OnExit_Attack2. NextState: %s", StateToStr(NextState), "\n");
	player->attackCollider->to_delete = true;
}

//-----------------------------------------------------------------------------------------
// Attack3 State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Attack3(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Attack3. PrevState: %s", StateToStr(PrevState), "\n");
	player->finishedAnimation = false;
	player->animationCountdown = 32;
	player->attack3.Reset();
	player->currentAnimation = &player->attack3;
	player->attackCollider = App->collision->AddCollider({ player->position.x, player->position.y, 35, 60 }, CPLAYER_ATTACK, std::bind(&Player::OnCollision, player, std::placeholders::_1));
}

void AnimationStateMachine::OnUpdate_Attack3()
{
	// LOG("OnUpdate_Attack3\n");
	if (player->animationCountdown <= 0) {
		player->finishedAnimation = true;
	}
	else {
		player->animationCountdown -= 1;
	}
	int colliderX = NULL;
	if (player->direction) {
		colliderX = player->position.x + player->collider->rect.w;
	}
	else {
		colliderX = player->position.x - player->attackCollider->rect.w;
	}
	player->attackCollider->SetPos(colliderX, player->position.y);
	if (player->finishedAnimation) {
		Idle();
	}
}

void AnimationStateMachine::OnExit_Attack3(State NextState)
{
	// LOG("OnExit_Attack3. NextState: %s", StateToStr(NextState), "\n");
	player->attackCollider->to_delete = true;
}

//-----------------------------------------------------------------------------------------
// Grab State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Grab(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Grab. PrevState: %s", StateToStr(PrevState), "\n");
}

void AnimationStateMachine::OnUpdate_Grab()
{
	// LOG("OnUpdate_Grab\n");
}

void AnimationStateMachine::OnExit_Grab(State NextState)
{
	// LOG("OnExit_Grab. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Punch State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Punch(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Punch. PrevState: %s", StateToStr(PrevState), "\n");
}

void AnimationStateMachine::OnUpdate_Punch()
{
	// LOG("OnUpdate_Punch\n");
}

void AnimationStateMachine::OnExit_Punch(State NextState)
{
	// LOG("OnExit_Punch. NextState: %s", StateToStr(NextState), "\n");
}

//-----------------------------------------------------------------------------------------
// Throw State
//-----------------------------------------------------------------------------------------
void AnimationStateMachine::OnEnter_Throw(State PrevState, const EventData* pData)
{
	// LOG("OnEnter_Throw. PrevState: %s", StateToStr(PrevState), "\n");
}

void AnimationStateMachine::OnUpdate_Throw()
{
	// LOG("OnUpdate_Throw\n");
}

void AnimationStateMachine::OnExit_Throw(State NextState)
{
	// LOG("OnExit_Throw. NextState: %s", StateToStr(NextState), "\n");
}