#include "Balls.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Module.h"
#include "Med_Balls.h"

Balls::Balls(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({0,0,41,41});
	
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 41, 41}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Balls::Update()
{

	B_Vy = B_Vy +( grav* Time);

	if (B_Vy > 380)//450
	{
		B_Vy = 350;//430
	}

	position.y = position.y + (B_Vy * Time) + (grav * (Time * Time));
	position.x = position.x + (B_Vx * Time);
	


	//position.x += 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Balls::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER_SHOT) {
		App->enemies->AddEnemy(Enemy_Type::Med_Ball, position.x + 10, position.y);
		App->enemies->AddEnemy(Enemy_Type::Med_Ball, position.x - 10, position.y);
	}
}

