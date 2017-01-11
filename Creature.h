#pragma once
#include "Entity.h"

class Creature :
	public Entity
{
public:
	Creature();
	~Creature();

	void TakeDamage(int damage);
	virtual void Die() {};

public:
	Animation* currentAnimation = nullptr;
	Animation* lastMovementAnimation = nullptr;
	Collider* collider = nullptr;
	Collider* attackCollider = nullptr;
	Animation idle;
	Animation right;
	Animation left;
	bool finishedAnimation = false;
	int animationCountdown = NULL;
	iPoint position;

protected:
	int maxHp = 10000;
	int currentHp = 10000;
};

