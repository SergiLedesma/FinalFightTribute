#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Creature.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "EnemyStateMachine.h"

enum BehaviourDecision {
	BDGORIGHT,
	BDGOLEFT,
	BDGOUP,
	BDGODOWN,
	BDIDLE,
	BDATTACK
};

class Enemy :
	public Creature
{
public:
	Enemy();
	~Enemy();
	
	bool Start();
	bool CleanUp();
	update_status Update();
	void OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType);
	void Die();
	void BehaviourTree();
	
public:
	Animation attack;
	int speed = 1;

private:
	int attackDelay = 20;
	EnemyStateMachine* Life;
	int maxDecisionCooldown = 5;
	int decisionCooldown = 5;
	int maxAttackCooldown = 10;
	int attackCooldown = 10;
	bool canAttack = false;
	BehaviourDecision decision = BDIDLE;
};

#endif // __ENEMY_H__