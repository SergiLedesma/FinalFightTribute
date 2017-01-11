#ifndef _ENEMYSTATEMACHINE_H_
#define _ENEMYSTATEMACHINE_H_

#include "StateMachine.h"
#include "MovementKeys.h"

class Enemy;

class EnemyEventData : public EventData {
public:
	EnemyEventData(MOVEMENTKEY direction) : direction(direction) {};
	virtual ~EnemyEventData() {};
public:
	MOVEMENTKEY direction;
};


class EnemyStateMachine : public StateMachine {
public:

	EnemyStateMachine(Enemy* enemy) : StateMachine(ST_COUNT), enemy(enemy) {}
	~EnemyStateMachine();

	void Update();

	// Supported Events:
	void Move(MOVEMENTKEY direction);
	void Attack();
	void Idle();

private:
	Enemy* enemy = nullptr;
	EnemyEventData* data = nullptr;

	// Enumeration of the states:
	enum EState {
#define ENEMY_STATE(_state, _func) _state,
#include "EnemyState.h"
#undef ENEMY_STATE
		ST_COUNT
	};

	// Function declaration for the states. Every states has 3 associated functions:
	// OnEnter_xxx, OnUpdate_xxx and OnExit_xxx
#define ENEMY_STATE(_state, _func) STATE_FUNCTION_DECLARATION(_func)
#include "EnemyState.h"
#undef ENEMY_STATE

	// Mapping of the states with their associated functions
	BEGIN_STATE_MAP
#define ENEMY_STATE(_state, _func) STATE_MAP_ENTRY(EnemyStateMachine, _func)
#include "EnemyState.h"
#undef ENEMY_STATE
	END_STATE_MAP

	// Converts a state to string
	const char * StateToStr(State state);
};

#endif // !_ENEMYSTATEMACHINE_H_