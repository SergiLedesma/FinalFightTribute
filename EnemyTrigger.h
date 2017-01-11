#ifndef __ENEMYTRIGGER_H__
#define __ENEMYTRIGGER_H__

#include "Trigger.h"
class EnemyTrigger :
	public Trigger
{
public:
	EnemyTrigger();
	~EnemyTrigger();

	void Shot();
};

#endif // __ENEMYTRIGGER_H__
