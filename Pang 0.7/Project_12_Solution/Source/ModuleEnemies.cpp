#include "ModuleEnemies.h"

#include "Application.h"
#include "ModuleFadeToBlack.h"

#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Collider.h"

#include "Enemy.h"
#include "Balls.h"
#include "Med_Balls.h"
#include "Med_Balls2.h"
#include "Small_Balls.h"
#include "Small_Balls2.h"
#include "VSmall_Balls.h"
#include "VSmall_Balls2.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel4.h"
#include "SceneLevel5.h"
#include "SceneLevel6.h"

#include "Breakable_Platform.h"



#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	c = 0;
	texture = App->textures->Load("Assets/Sprites/entities.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
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

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		/*if (enemies[i] != nullptr)
		{

		}*/
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::Big_Ball:
				enemies[i] = new Balls(info.x, info.y);
				break;
			case Enemy_Type::Med_Ball:
				enemies[i] = new Med_Balls(info.x, info.y);
				break;
			case Enemy_Type::Med_Ball2:
				enemies[i] = new Med_Balls2(info.x, info.y);
				break;
			case Enemy_Type::Small_Ball:
				enemies[i] = new Small_Balls(info.x, info.y);
				break;
			case Enemy_Type::Small_Ball2:
				enemies[i] = new Small_Balls2(info.x, info.y);
				break;
			case Enemy_Type::VSmall_Ball:
				enemies[i] = new VSmall_Balls(info.x, info.y);
				break;
			case Enemy_Type::VSmall_Ball2:
				enemies[i] = new VSmall_Balls2(info.x, info.y);
				break;
			case Enemy_Type::BreakablePlatform:
				enemies[i] = new BreakablePlatform(info.x, info.y);
				break;
			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}



void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL1)//pared up
		{
			App->enemies->enemies[i]->position.y = 11;
			App->enemies->enemies[i]->B_Vy *= -1;

		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL2)//pared down
		{

			App->enemies->enemies[i]->position.y -= 10;
			App->enemies->enemies[i]->B_Vy *= -1;
		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL3)//pared iz
		{
			App->enemies->enemies[i]->position.x += 5;
			App->enemies->enemies[i]->B_Vx = -(App->enemies->enemies[i]->B_Vx);

		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL4)//pared derecha
		{
			App->enemies->enemies[i]->position.x -= 4;
			App->enemies->enemies[i]->B_Vx = -(App->enemies->enemies[i]->B_Vx);
		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMUp)
		{
			App->enemies->enemies[i]->position.y += 10;
			App->enemies->enemies[i]->B_Vy *= -1;

		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMDown)//pared down
		{

			App->enemies->enemies[i]->position.y -= 10;
			App->enemies->enemies[i]->B_Vy *= -1;
		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMLeft)//pared iz
		{
			App->enemies->enemies[i]->position.x = 11;
			App->enemies->enemies[i]->B_Vx = -(App->enemies->enemies[i]->B_Vx);

		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::BPLATFORMRight)//pared derecha
		{
			App->enemies->enemies[i]->position.x -= 4;
			App->enemies->enemies[i]->B_Vx = -(App->enemies->enemies[i]->B_Vx);
		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && (c2->type == Collider::Type::PLAYER_SHOT || c2->type == Collider::Type::VULCAN || c2->type == Collider::Type::POWERWIRE))
		{
			App->player->score += 200;
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			delete enemies[i];
			if (c1->type == Collider::Type::BPLATFORM)
			{
				c = c;
			}
			else {
				c++;
			}
			enemies[i] = nullptr;
			//1st Level
			if (c == 15 && App->player->level1 == true) {
				App->sceneLevel_1->CleanUp();
				App->player->start = true;
				App->player->totalscore = App->player->score;
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
			}
			if (c == 15 && App->player->level2 == true)
			{
				App->sceneLevel_2->CleanUp();
				App->player->start = true;
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3, 90);
				App->player->totalscore = App->player->score;
			}
			if (c == 18 && App->player->level3 == true)
			{
				App->sceneLevel_3->CleanUp();
				App->player->start = true;
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
				App->player->totalscore = App->player->score;
			}
			if (c == 15 && App->player->level4 == true)
			{
				App->sceneLevel_4->CleanUp();
				App->player->start = true;
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_5, 90);
				App->player->totalscore = App->player->score;
			}
			if (c == 22 && App->player->level5 == true)
			{
				App->sceneLevel_5->CleanUp();
				App->player->start = true;
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_6, 90);
				App->player->totalscore = App->player->score;
			}
			if (c == 30 && App->player->level6 == true)
			{
				App->sceneLevel_6->CleanUp();
				App->player->start = true;
				App->fade->FadeToBlack(this, (Module*)App->sceneWin, 90);
				App->player->totalscore = App->player->score;
			}
			break;
		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == Collider::Type::PLAYER)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			for (int i = 0; i < MAX_ENEMIES; i++)
			{
				delete enemies[i];
				enemies[i] = nullptr;


			}

		}
	}
}
