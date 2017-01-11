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
	if (currentHp > 0) {
		currentHp -= damage;
		LOG("%d", currentHp);
		if (currentHp <= 0) {
			currentHp = 0;
			Die();
		}
	}
}