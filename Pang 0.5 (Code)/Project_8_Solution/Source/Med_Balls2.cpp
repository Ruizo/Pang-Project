#include "Med_Balls2.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Module.h"
#include "Balls.h"
#include "ModuleBoosters.h"

Med_Balls2::Med_Balls2(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 59,829,32,26 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 32, 26 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Med_Balls2::Update()
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

void Med_Balls2::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER_SHOT) {
		App->enemies->AddEnemy(Enemy_Type::Small_Ball, position.x + 10, position.y);
		App->enemies->AddEnemy(Enemy_Type::Small_Ball2, position.x - 10, position.y);
	}
}