#ifndef __FxLibrary_H__
#define __FxLibrary_H__

#include "Module.h"

class FxLibrary :
	public Module
{
public:
	FxLibrary(bool active = true);
	~FxLibrary();

	bool Start();

public:
	uint fxPunch1 = 0;
	uint fxPunch2 = 0;
	uint fxPunch3 = 0;
	uint fxPunch4 = 0;
	uint opening = 0;
	uint fxBarrel = 0;
};

#endif //__FxLibrary_H__