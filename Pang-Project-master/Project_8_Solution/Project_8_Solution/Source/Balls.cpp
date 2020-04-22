#include "Balls.h"

#include "Application.h"
#include "ModuleCollisions.h"

Balls::Balls(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({0,0,41,41});
	
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 41, 41}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Balls::Update()
{
	LOG("%d\n", B_Vy);
	B_Vy = B_Vy +  (grav * Time);

	position.y = position.y + (B_Vy * Time) + (grav * (Time * Time));
	position.x = position.x + (B_Vx * Time);

	//position.x += 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

