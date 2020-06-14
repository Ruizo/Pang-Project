#include "Med_Balls.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Module.h"
#include "Balls.h"
#include "ModuleBoosters.h"

Med_Balls::Med_Balls(int x, int y) : Enemy(x, y)
{
	if (App->player->level1 || App->player->level4)
	{
		flyAnim.PushBack({ 59,829,32,26 });
	}
	if (App->player->level2 || App->player->level5)
	{
		flyAnim.PushBack({ 59,879,32,26 });
	}
	if (App->player->level3 || App->player->level6)
	{
		flyAnim.PushBack({ 59,928,32,26 });
	}

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 32, 26 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Med_Balls::Update()
{
	if (App->Boosters->stoptime != true) {
		if (B_Vy > 4.5f)
		{
			B_Vy = 4.3f;
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

void Med_Balls::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->deathExplosion2, position.x - 3, position.y - 2);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER_SHOT || c2->type == Collider::Type::VULCAN || c2->type == Collider::Type::POWERWIRE) {
		App->enemies->AddEnemy(Enemy_Type::Small_Ball, position.x + 10, position.y);
		App->enemies->AddEnemy(Enemy_Type::Small_Ball2, position.x - 10, position.y);


	}
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


