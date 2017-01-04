#ifndef _ANIMATIONSTATEMACHINE_H_
#define _ANIMATIONSTATEMACHINE_H_

#include "StateMachine.h"
#include "MovementKeys.h"

class Player;

class AnimationEventData : public EventData {
public:
	AnimationEventData(MOVEMENTKEYS direction) : direction(direction) {};
	virtual ~AnimationEventData() {};
public:
	MOVEMENTKEYS direction;
};


class AnimationStateMachine : public StateMachine {
public:

	AnimationStateMachine(Player* player) : StateMachine(ST_COUNT), player(player) {}
	~AnimationStateMachine() { RELEASE(player); delete player; RELEASE(data); delete data;  }

	void Update();

	// Supported Events:
	void Move(MOVEMENTKEYS direction);
	void Jump(MOVEMENTKEYS direction);
	void Attack();
	void Idle();

private:
	Player* player = nullptr;
	AnimationEventData* data = nullptr;
	int playerRealY;

	// Enumeration of the states:
	enum EState {
#define ANIMATION_STATE(_state, _func) _state,
#include "AnimationState.h"
#undef ANIMATION_STATE
		ST_COUNT
	};

	// Function declaration for the states. Every states has 3 associated functions:
	// OnEnter_xxx, OnUpdate_xxx and OnExit_xxx
#define ANIMATION_STATE(_state, _func) STATE_FUNCTION_DECLARATION(_func)
#include "AnimationState.h"
#undef ANIMATION_STATE

	// Mapping of the states with their associated functions
	BEGIN_STATE_MAP
#define ANIMATION_STATE(_state, _func) STATE_MAP_ENTRY(AnimationStateMachine, _func)
#include "AnimationState.h"
#undef ANIMATION_STATE
	END_STATE_MAP

	// Converts a state to string
	const char * StateToStr(State state);
};

#endif // !_ANIMATIONSTATEMACHINE_H_