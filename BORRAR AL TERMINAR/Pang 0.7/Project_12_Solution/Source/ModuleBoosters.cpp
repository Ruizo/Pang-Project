#include "ModuleBoosters.h"

#include "Application.h"
#include "ModuleFadeToBlack.h"

#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Collider.h"

#include "Booster.h"
#include "DoubleWire.h"
#include "Invincibility.h"
#include "StopTime.h"
#include "SlowTime.h"


#include "Breakable_Platform.h"



#define SPAWN_MARGIN 50


ModuleBoosters::ModuleBoosters(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_BOOSTERS; ++i)
		Boosters[i] = nullptr;
}

ModuleBoosters::~ModuleBoosters()
{

}

bool ModuleBoosters::Start()
{
	c = 0;
	texture = App->textures->Load("Assets/Sprites/entities.png");
	BoosterDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	return true;
}

Update_Status ModuleBoosters::Update()
{
	HandleBoostersSpawn();

	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (Boosters[i] != nullptr)
			Boosters[i]->Update();
	}

	HandleBoostersDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBoosters::PostUpdate()
{
	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (Boosters[i] != nullptr)
			Boosters[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBoosters::CleanUp()
{
	LOG("Freeing all Boosters");

	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (Boosters[i] != nullptr)
		{
			delete Boosters[i];
			Boosters[i] = nullptr;
		}
	}
	
	return true;
}

bool ModuleBoosters::AddBooster(Booster_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (spawnQueue[i].type == Booster_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleBoosters::HandleBoostersSpawn()
{
	// Iterate all the Boosters queue
	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (spawnQueue[i].type != Booster_Type::NO_TYPE)
		{
			// Spawn a new Booster if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning Booster at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnBooster(spawnQueue[i]);
				spawnQueue[i].type = Booster_Type::NO_TYPE; // Removing the newly spawned Booster from the queue
			}
		}
	}
}

void ModuleBoosters::HandleBoostersDespawn()
{
	// Iterate existing Boosters
	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		/*if (Boosters[i] != nullptr)
		{

		}*/
	}
}

void ModuleBoosters::SpawnBooster(const BoosterSpawnpoint& info)
{
	// Find an empty slot in the Boosters array
	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (Boosters[i] == nullptr)
		{
			switch (info.type)
			{
			case Booster_Type::DOUBLEWIRE:
				Boosters[i] = new DoubleWire(info.x, info.y);
				break;
			case Booster_Type::INVINCIBLE:
				Boosters[i] = new Invincibility(info.x, info.y);
				break;
			case Booster_Type::STOPTIME:
				Boosters[i] = new StopTime(info.x, info.y);
				break;
			case Booster_Type::SLOWTIME:
				Boosters[i] = new SlowTime(info.x, info.y);
				break;
			}
			Boosters[i]->texture = texture;
			Boosters[i]->destroyedFx = BoosterDestroyedFx;
			break;
		}
	}

}



void ModuleBoosters::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_BOOSTERS; ++i)
	{
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL1)//pared up
		{
			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;

		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL2)//pared down
		{

			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;
		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL3)//pared iz
		{
			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;

		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL4)//pared derecha
		{
			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;
		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMUp)//pared up
		{
			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;

		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMDown)//pared down
		{

			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;
		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMLeft)//pared iz
		{
			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;

		}
		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMRight)//pared derecha
		{
			App->Boosters->Boosters[i]->position.y = 184;
			App->Boosters->Boosters[i]->B_Vy *= 1;
		}

		if (Boosters[i] != nullptr && Boosters[i]->GetCollider() == c1 && c2->type == Collider::Type::PLAYER)
		{
			Boosters[i]->OnCollision(c2); //Notify the Booster of a collision
			for (int i = 0; i < MAX_BOOSTERS; i++)
			{
				delete Boosters[i];
				Boosters[i] = nullptr;


			}

		}
	}
}