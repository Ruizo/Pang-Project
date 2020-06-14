#include "VSmall_Balls2.h"

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

VSmall_Balls2::VSmall_Balls2(int x, int y) : Enemy(x, y)
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

void VSmall_Balls2::Update()
{
	if (App->Boosters->stoptime != true) {
		if (B_Vy > 4.3f)
		{
			B_Vy = 4.0f;
		}
		position.x -= B_Vx;
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

void VSmall_Balls2::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->deathExplosion4, position.x, position.y);
	App->audio->PlayFx(destroyedFx);

	switch (App->enemies->random) {
	case 0:
		App->Boosters->AddBooster(Booster_Type::DYNAMITE, position.x, position.y);
		break;
	case 1:
		App->Boosters->AddBooster(Booster_Type::DOUBLEWIRE, position.x, position.y);
		break;
	case 3:
		App->Boosters->AddBooster(Booster_Type::POWERWIRE, position.x, position.y);
		break;
	case 4:
		App->Boosters->AddBooster(Booster_Type::STOPTIME, position.x, position.y);
		break;
	case 5:
		App->Boosters->AddBooster(Booster_Type::INVINCIBLE, position.x, position.y);
		break;
	case 6:
		App->Boosters->AddBooster(Booster_Type::SLOWTIME, position.x, position.y);
		break;
	case 7:
		App->Boosters->AddBooster(Booster_Type::VULCAN, position.x, position.y);
		break;
	}
}