#pragma once
#include "Destructible.h"
class Barrel :
	public Destructible
{
public:
	Barrel();
	~Barrel();
	bool Start();
};

