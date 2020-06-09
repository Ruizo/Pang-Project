#include "VSmall_Balls.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Module.h"
#include "Small_Balls.h"
#include "Small_Balls2.h"

VSmall_Balls::VSmall_Balls(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 113, 839, 8, 7 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 8, 7 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void VSmall_Balls::Update()
{
	if (B_Vy > 4.8f)
	{
		B_Vy = 4.5f;
	}
	position.x += B_Vx;
	position.y -= (B_Vy + grav);
	B_Vy -= grav;

	Enemy::Update();
}