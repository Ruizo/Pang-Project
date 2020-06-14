#include "PowerWire.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

PowerWire::PowerWire(bool startEnabled) : Module(startEnabled)
{
	name = "particles";

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

	

}

PowerWire::~PowerWire()
{

}

bool PowerWire::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/entities.png");

	// Explosion particle
	powerwire.anim.PushBack({ 35, 1146, 10, 11 });
	powerwire.anim.PushBack({ 48, 1146, 10, 25 });
	powerwire.anim.PushBack({ 35, 1146, 10, 39 });
	powerwire.anim.PushBack({ 48, 1146, 10, 53 });
	powerwire.anim.PushBack({ 35, 1146, 10, 67 });
	powerwire.anim.PushBack({ 48, 1146, 10, 81 });
	powerwire.anim.PushBack({ 35, 1146, 10, 95 });
	powerwire.anim.PushBack({ 48, 1146, 10, 109 });
	powerwire.anim.PushBack({ 35, 1146, 10, 123 });
	powerwire.anim.PushBack({ 48, 1146, 10, 137 });
	powerwire.anim.PushBack({ 35, 1146, 10, 151 });
	powerwire.anim.PushBack({ 48, 1146, 10, 165 });
	powerwire.anim.PushBack({ 35, 1146, 10, 179 });
	powerwire.anim.PushBack({ 48, 1146, 10, 193 });
	powerwire.anim.PushBack({ 35, 1146, 10, 207 });
	idleAnim.PushBack({ 35, 1146, 10, 207 });

	powerwire.anim.loop = false;
	powerwire.speed.y = -3;
	powerwire.lifetime = 500;
	powerwire.anim.speed = 0.21f;

	return true;
}

Update_Status PowerWire::PreUpdate()
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

bool PowerWire::CleanUp()
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

void PowerWire::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			if (c2->type != Collider::Type::WALL1) {
				powerwire.speed.y = -3;
				App->player->shoot = true;
				yes = false;
				delete particles[i];
				particles[i] = nullptr;
				break;
			}
			else if (c2->type == Collider::Type::WALL1){
				yes = true;

				if (currentAnimation != &idleAnim) {

					idleAnim.Reset();
					currentAnimation = &idleAnim;
				}
				powerwire.speed.y = 0;
				break;

			}
			
			
		}

	}
}

Update_Status PowerWire::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		PowerWireP* PowerWireP = particles[i];
		if (PowerWireP == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (PowerWireP->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status PowerWire::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		PowerWireP* PowerWireP = particles[i];

		if (PowerWireP != nullptr && PowerWireP->isAlive)
		{
			App->render->Blit(texture, PowerWireP->position.x, PowerWireP->position.y, &(PowerWireP->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

PowerWireP* PowerWire::AddParticle(const PowerWireP& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	PowerWireP* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			PowerWireP* p = new PowerWireP(particle);

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