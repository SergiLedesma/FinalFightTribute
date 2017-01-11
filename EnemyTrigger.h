#pragma once
#include "Trigger.h"
class EnemyTrigger :
	public Trigger
{
public:
	EnemyTrigger();
	~EnemyTrigger();

	void Shot();
};

