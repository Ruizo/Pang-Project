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
	texture = App->textures->Load("Assets/Sprites/particles.png");

	// Explosion particle
	laser.anim.PushBack({ 0, 0, 10, 11 });
	laser.anim.PushBack({ 12, 0, 10, 25 });
	laser.anim.PushBack({ 0, 0, 10, 39 });
	laser.anim.PushBack({ 12, 0, 10, 53 });
	laser.anim.PushBack({ 0, 0, 10, 67 });
	laser.anim.PushBack({ 12, 0, 10, 81 });
	laser.anim.PushBack({ 0, 0, 10, 95 });
	laser.anim.PushBack({ 12, 0, 10, 109 });
	laser.anim.PushBack({ 0, 0, 10, 123 });
	laser.anim.PushBack({ 12, 0, 10, 137 });
	laser.anim.PushBack({ 0, 0, 10, 151 });
	laser.anim.PushBack({ 12, 0, 10, 165 });
	laser.anim.PushBack({ 0, 0, 10, 179 });
	laser.anim.PushBack({ 12, 0, 10, 193 });
	laser.anim.PushBack({ 0, 0, 10, 207 });
	laser.anim.PushBack({ 12, 0, 10, 221 });
	laser.anim.PushBack({ 0, 0, 10, 235 });
	laser.anim.PushBack({ 12, 0, 10, 249 });
	laser.anim.PushBack({ 0, 0, 10, 263 });
	laser.anim.PushBack({ 27, 0, 10, 267 });
	laser.anim.PushBack({ 40, 0, 10, 267 });
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