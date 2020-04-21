#include "Balls.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Collider.h"

Balls::Balls(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({0,0,41,41});
	/*flyAnim.PushBack({38, 6, 24, 24});
	flyAnim.PushBack({71, 6, 24, 24});
	flyAnim.PushBack({104, 6, 24, 24});
	flyAnim.PushBack({137, 6, 24, 24});
	flyAnim.PushBack({170, 6, 24, 24});
	flyAnim.PushBack({203, 6, 24, 24});
	flyAnim.PushBack({236, 6, 24, 24});*/
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;
	
	collider = App->collisions->AddCollider({0, 0, 41, 39}, Collider::Type::ENEMY, (Module*)App->enemies);


}

void Balls::Update()
{
	speed.y = -2.0f *1; 
	speed.x = 1.3f * 5; 
	
	if (speed.y > 7.0f) { speed.y = 7.0f; }

	position.x += speed.x;
	position.y += speed.y;
	speed.y += GRAVITY;
	

	
/*	waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 1;*/

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
void OnCollision(Collider* c1, Collider *  c3 ) {

	
}
