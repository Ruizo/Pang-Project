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
	if (App->Boosters->stoptime != true) {
		if (B_Vy > 4.8f)
		{
			B_Vy = 4.5f;
		}
		position.x -= B_Vx;
		position.y -= (B_Vy + grav);
		B_Vy -= grav;
	}

	Enemy::Update();
}

void Small_Balls2::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER_SHOT) {
		App->enemies->AddEnemy(Enemy_Type::VSmall_Ball, position.x + 10, position.y);
		App->enemies->AddEnemy(Enemy_Type::VSmall_Ball2, position.x - 10, position.y);


	}
}