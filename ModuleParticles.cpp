#include <math.h>
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "EntityManager.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	//graphics = App->textures->Load("PATH.PNG");

	//PARTICLENAME.audio = App->audio->LoadFx("PATH.WAV");
	//PARTICLENAME.collider = new Collider({ 0, 0, 20, 12 }, nullptr);
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end(); )
	{
		Particle* p = *it;

		if(p->Update() == false)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
		{ 
			App->renderer->AddBlit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), 1.0f);
			++it;
		}
	}


	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y)
{
	Particle * p = new Particle(particle);
	p->position = { x, y };
	active.push_back(p);
	
}

SDL_Texture* ModuleParticles::GetGraphics() {
	return graphics;
}

// -------------------------------------------------------------
// -------------------------------------------------------------


Particle::Particle()
{}

Particle::Particle(const Particle& p) 
{
	position = p.position;
	speed = p.speed;
	lifeSpan = p.lifeSpan;
	damage = p.damage;
	direction = p.direction;
	anim = p.anim;
	audio = p.audio;
	collider = p.collider;
	if (collider != nullptr) {
		if (collider->rect.h != 0 && collider->rect.w != 0) {
			collider = App->collision->AddCollider(p.collider->rect, CPLAYER_ATTACK, std::bind(&Particle::OnCollision, this, std::placeholders::_1, std::placeholders::_2));
		}
	}
}

Particle::~Particle()
{

}

bool Particle::Update()
{
	bool ret = true;

	if (to_delete == true) {
		ret = false;
	}
	else if (lifeSpan <= 0) {
		collider->to_delete = true;
		to_delete = true;
		ret = false;
	}
	else {
		lifeSpan--;
		this->position.x = this->position.x + (int)speed;
		collider->SetPos(this->position.x, this->position.y);
	}

	return ret;
}

void Particle::OnCollision(std::map<MOVEMENTKEY, bool> direction, CollisionType otherType) {
	LOG("Collision on particle");
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	collider->to_delete = true;
	to_delete = true;
}