#include "Med_Balls.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Module.h"

Med_Balls::Med_Balls(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 42,0,21,21 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 21, 21 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Med_Balls::Update()
{

	B_Vy = B_Vy + (grav * Time);

	if (B_Vy > 400)
	{
		B_Vy = 390;
	}

	position.y = position.y + (B_Vy * Time) + (grav * (Time * Time));
	position.x = position.x + (B_Vx * Time);


	//position.x += 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}


