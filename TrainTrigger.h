#pragma once
#include "Trigger.h"
class TrainTrigger :
	public Trigger
{
public:
	TrainTrigger();
	~TrainTrigger();

	void Shot();
};

