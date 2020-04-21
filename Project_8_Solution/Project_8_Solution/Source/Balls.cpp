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
	B_Vy = B_Vy + (grav * deltaTime);

	position.y = position.y + (B_Vy * deltaTime) + (grav * (deltaTime * deltaTime));
	position.x = position.x + (B_Vx * deltaTime);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

