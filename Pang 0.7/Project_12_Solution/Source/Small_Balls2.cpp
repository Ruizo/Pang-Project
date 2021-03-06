#include "Small_Balls2.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Module.h"
#include "Med_Balls.h"
#include "Med_Balls2.h"
#include "ModuleBoosters.h"

Small_Balls2::Small_Balls2(int x, int y) : Enemy(x, y)
{
	if (App->player->level1 || App->player->level4)
	{
		flyAnim.PushBack({ 93, 835, 16, 14 });
	}
	if (App->player->level2 || App->player->level5)
	{
		flyAnim.PushBack({ 93, 885, 16, 14 });
	}
	if (App->player->level3 || App->player->level6)
	{
		flyAnim.PushBack({ 93, 934, 16, 14 });
	}

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 16, 14 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Small_Balls2::Update()
{
	if (App->player->dead != true) {
		if (App->Boosters->slowtime != true) {
			if (App->Boosters->stoptime != true) {
				grav = 0.1f;
				if (B_Vy > 3.5f)
				{
					B_Vy = 3.2f;
				}
				position.x -= B_Vx;
				position.y -= (B_Vy + grav);
				B_Vy -= grav;
			}
		}

		if (App->Boosters->slowtime == true) {
			if (App->Boosters->stoptime != true) {
				App->Boosters->tempSl++;
				grav = 0.025f;
				if (B_Vy > 4.f)
				{
					B_Vy = 3.f;
				}
				position.x -= B_Vx;
				position.y -= (B_Vy + grav);
				B_Vy -= grav;
				if (App->Boosters->tempSl == 600) {
					App->Boosters->slowtime = false;
					App->Boosters->tempSl = 0;

				}
			}

		}

		if (App->Boosters->stoptime == true) {
			App->Boosters->tempSt++;
			if (App->Boosters->tempSt == 300) {
				App->Boosters->stoptime = false;
				App->Boosters->tempSt = 0;
			}

		}
	}
	else {

	}
	Enemy::Update();
}

void Small_Balls2::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->deathExplosion3, position.x - 1, position.y - 1);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER_SHOT || c2->type == Collider::Type::VULCAN || c2->type == Collider::Type::POWERWIRE) {
		App->enemies->AddEnemy(Enemy_Type::VSmall_Ball, position.x + 10, position.y);
		App->enemies->AddEnemy(Enemy_Type::VSmall_Ball2, position.x - 10, position.y);


	}
	switch (App->enemies->random) {
	case 0:
		App->Boosters->AddBooster(Booster_Type::DYNAMITE, position.x, position.y);
		break;
	case 1:
		App->Boosters->AddBooster(Booster_Type::DOUBLEWIRE, position.x, position.y);
		break;
	/*case 3:
		App->Boosters->AddBooster(Booster_Type::POWERWIRE, position.x, position.y);
		break;*/
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