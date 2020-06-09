#include "Breakable_Platform.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Module.h"


BreakablePlatform::BreakablePlatform(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 264, 619, 31, 7 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ x, y, 31, 7 }, Collider::Type::BPLATFORM, (Module*)App->enemies);
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