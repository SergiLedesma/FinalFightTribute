#include "Creature.h"
#include "Application.h"
#include "ModuleAudio.h"



Creature::Creature()
{
}


Creature::~Creature()
{
}

void Creature::TakeDamage(int damage)
{
	currentHp -= damage;
	LOG("%d", currentHp);
	if (currentHp <= 0) {
		Die();
	}
}