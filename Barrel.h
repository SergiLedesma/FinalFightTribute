#ifndef __BARREL_H__
#define __BARREL_H__

#include "Destructible.h"
class Barrel :
	public Destructible
{
public:
	Barrel();
	~Barrel();
	bool Start();
};

#endif // __BARREL_H__