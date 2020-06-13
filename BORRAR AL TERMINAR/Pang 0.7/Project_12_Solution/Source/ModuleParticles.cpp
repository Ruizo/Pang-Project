#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	name = "particles";

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/entities.png");

	deathExplosion1.anim.PushBack({ 63, 1095, 28, 47 });
	deathExplosion1.anim.PushBack({ 99, 1095, 41, 47 });
	deathExplosion1.anim.PushBack({ 148, 1095, 48, 48 });
	deathExplosion1.lifetime = 18;
	deathExplosion1.anim.speed = 0.15f;

	deathExplosion2.anim.PushBack({ 47, 1047, 19, 14 });
	deathExplosion2.anim.PushBack({ 75, 1044, 26, 25 });
	deathExplosion2.anim.PushBack({ 110, 1042, 31, 29 });
	deathExplosion2.lifetime = 18;
	deathExplosion2.anim.speed = 0.15f;

	deathExplosion3.anim.PushBack({ 31, 1006, 8, 8 });
	deathExplosion3.anim.PushBack({ 48, 1002, 14, 10 });
	deathExplosion3.anim.PushBack({ 71, 1002, 15, 16 });
	deathExplosion3.lifetime = 18;
	deathExplosion3.anim.speed = 0.15f;

	deathExplosion4.anim.PushBack({ 7, 971, 4, 4 });
	deathExplosion4.anim.PushBack({ 20, 971, 6, 5 });
	deathExplosion4.anim.PushBack({ 35, 970, 9, 8 });
	deathExplosion4.lifetime = 18;
	deathExplosion4.anim.speed = 0.15f;

	platformDeath1.anim.PushBack({ 48, 619, 31, 7 });
	platformDeath1.anim.PushBack({ 88, 619, 31, 7 });
	platformDeath1.anim.PushBack({ 128, 619, 31, 7 });
	platformDeath1.anim.PushBack({ 166, 619, 31, 7 });
	platformDeath1.lifetime = 18;
	platformDeath1.anim.speed = 0.15f;

	platformDeath2.anim.PushBack({ 49, 795, 31, 7 });
	platformDeath2.anim.PushBack({ 89, 795, 31, 7 });
	platformDeath2.anim.PushBack({ 129, 795, 31, 7 });
	platformDeath2.anim.PushBack({ 167, 795, 31, 7 });
	platformDeath2.lifetime = 18;
	platformDeath2.anim.speed = 0.15f;

	platformDeath3.anim.PushBack({ 24, 475, 7, 23 });
	platformDeath3.anim.PushBack({ 40, 475, 7, 23 });
	platformDeath3.anim.PushBack({ 56, 475, 7, 23 });
	platformDeath3.anim.PushBack({ 71, 475, 7, 23 });
	platformDeath3.lifetime = 18;
	platformDeath3.anim.speed = 0.15f;

	platformDeath4.anim.PushBack({ 33, 731, 15, 7 });
	platformDeath4.anim.PushBack({ 57, 731, 15, 7 });
	platformDeath4.anim.PushBack({ 81, 731, 15, 7 });
	platformDeath4.anim.PushBack({ 101, 731, 15, 7 });
	platformDeath4.lifetime = 18;
	platformDeath4.anim.speed = 0.15f;

	laser.anim.PushBack({ 8, 1146, 10, 11 });
	laser.anim.PushBack({ 20, 1146, 10, 25 });
	laser.anim.PushBack({ 8, 1146, 10, 39 });
	laser.anim.PushBack({ 20, 1146, 10, 53 });
	laser.anim.PushBack({ 8, 1146, 10, 67 });
	laser.anim.PushBack({ 20, 1146, 10, 81 });
	laser.anim.PushBack({ 8, 1146, 10, 95 });
	laser.anim.PushBack({ 20, 1146, 10, 109 });
	laser.anim.PushBack({ 8, 1146, 10, 123 });
	laser.anim.PushBack({ 20, 1146, 10, 137 });
	laser.anim.PushBack({ 8, 1146, 10, 151 });
	laser.anim.PushBack({ 20, 1146, 10, 165 });
	laser.anim.PushBack({ 8, 1146, 10, 179 });
	laser.anim.PushBack({ 20, 1146, 10, 193 });
	laser.anim.PushBack({ 8, 1146, 10, 207 });
	laser.anim.PushBack({ 20, 1146, 10, 221 });
	laser.anim.PushBack({ 8, 1146, 10, 235 });
	laser.anim.PushBack({ 20, 1146, 10, 249 });
	laser.anim.PushBack({ 8, 1146, 10, 263 });
	laser.anim.PushBack({ 48, 1146, 10, 267 });
	laser.anim.PushBack({ 35, 1146, 10, 267 });
	laser.speed.y = -3;
	laser.lifetime = 360;
	laser.anim.speed = 0.21f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			if (App->player->shoots == 2 && App->player->doubleshot == true) {
				App->player->shoot = true;
				App->player->shoots = 0;
			}
			if (App->player->doubleshot == false) {
				App->player->shoot = true;
			}
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider({ 0, 0, 10, 11 }, colliderType, this);
			particles[i] = p;
			break;
		}
	}

	return newParticle;
}