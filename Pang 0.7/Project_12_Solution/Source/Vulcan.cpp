#include "Vulcan.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

Vulcan::Vulcan(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

Vulcan::~Vulcan()
{

}

bool Vulcan::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/entities.png");

	//vulcan.anim.PushBack({ 100, 262, 4, 8 });
	//vulcan.anim.PushBack({ 112, 262, 8, 8 });
	//vulcan.anim.PushBack({ 128, 262, 12, 8 });
	vulcan.anim.PushBack({ 148, 263, 15, 6 });
	vulcan.anim.PushBack({ 172, 261, 14, 9 });

	vulcan.anim.loop;
	vulcan.speed.y = -4;
	vulcan.lifetime = 360;
	vulcan.anim.speed = 0.11f;

	return true;
}

bool Vulcan::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void Vulcan::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			if (App->player->shoots == 2 && App->player->VulcanB == true) {
				App->player->shoot = true;
				App->player->shoots = 0;
			}
			if (App->player->VulcanB == false) {
				App->player->shoot = true;
			}
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

Update_Status Vulcan::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Vulcan::PostUpdate()
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

void Vulcan::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
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
				p->collider = App->collisions->AddCollider({ 0, 0, 15, 9 }, colliderType, this);
			particles[i] = p;
			break;
		}
	}
}