#include "VSmall_Balls.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Module.h"
#include "Small_Balls.h"
#include "Small_Balls2.h"
#include "ModuleBoosters.h"

VSmall_Balls::VSmall_Balls(int x, int y) : Enemy(x, y)
{
	if (App->player->level1 || App->player->level4)
	{
		flyAnim.PushBack({ 113, 839, 8, 7 });
	}
	if (App->player->level2 || App->player->level5)
	{
		flyAnim.PushBack({ 113, 889, 8, 7 });
	}
	if (App->player->level3 || App->player->level6)
	{
		flyAnim.PushBack({ 113, 938, 8, 7 });
	}

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 8, 7 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void VSmall_Balls::Update()
{
	if (App->Boosters->stoptime != true) {
		if (B_Vy > 4.8f)
		{
			B_Vy = 4.5f;
		}
		position.x += B_Vx;
		position.y -= (B_Vy + grav);
		B_Vy -= grav;
	}
	if (App->Boosters->stoptime == true) {
		App->Boosters->tempSt++;
		if (App->Boosters->tempSt == 300) {
			App->Boosters->stoptime = false;
			App->Boosters->tempSt = 0;
		}

	}

	Enemy::Update();
}