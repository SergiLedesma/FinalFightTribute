#ifndef __ENDINGTRIGGER_H__
#define __ENDINGTRIGGER_H__

#include "Trigger.h"
class EndingTrigger :
	public Trigger
{
public:
	EndingTrigger();
	~EndingTrigger();

	void Shot();
};

#endif // __ENDINGTRIGGER_H__