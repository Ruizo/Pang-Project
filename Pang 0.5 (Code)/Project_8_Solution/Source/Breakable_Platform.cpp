#include "Breakable_Platform.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Module.h"


BreakablePlatform::BreakablePlatform(int x, int y) : Enemy(x, y)
{
	if (App->player->level2)
	{
		flyAnim.PushBack({ 264, 619, 31, 7 });
	}
	if (App->player->level3)
	{
		flyAnim.PushBack({ 304, 619, 31, 7 });
	}
	if (App->player->level5)
	{
		flyAnim.PushBack({ 8, 475, 7, 23 });
	}
	if (App->player->level6)
	{
		flyAnim.PushBack({ 9, 731, 15, 7 });
	}

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	if (App->player->level1)
	{
		collider = App->collisions->AddCollider({ x, y, 31, 7 }, Collider::Type::BPLATFORM, (Module*)App->enemies);
	}
	if (App->player->level5)
	{
		collider = App->collisions->AddCollider({ x, y, 7, 23 }, Collider::Type::BPLATFORM, (Module*)App->enemies);
	}
	if (App->player->level6)
	{
		collider = App->collisions->AddCollider({ x, y, 15, 7 }, Collider::Type::BPLATFORM, (Module*)App->enemies);
	}
}

void BreakablePlatform::Update()
{
	Enemy::Update();
}

void BreakablePlatform::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
}