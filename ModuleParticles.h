#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"

struct SDL_Texture;

struct Particle
{
	bool to_delete = false;

	float speed;
	int lifeSpan;
	float damage;
	iPoint direction;
	iPoint position;
	Animation anim;
	ModuleAudio audio;

	Collider* collider;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
	void OnCollision();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y); // feel free to expand this call

	SDL_Texture * GetGraphics();

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> active;

public:

	// prototype particles go here ...
	Particle laser;
	Particle explosion;
};

#endif // __MODULEPARTICLES_H__