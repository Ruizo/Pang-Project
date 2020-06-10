#include "Balls.h"

#include "Enemy.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "Module.h"
#include "Med_Balls.h"
#include "Med_Balls2.h"
#include "ModuleBoosters.h"

Balls::Balls(int x, int y) : Enemy(x, y)
{

	flyAnim.PushBack({ 8,822,48,40 });
	flyAnim.loop = false;

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 47, 40}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Balls::Update()
{
	if (App->Boosters->slowtime != true) {
		if (App->Boosters->stoptime != true) {
			if (B_Vy > 4.8f)
			{
				B_Vy = 4.5f;
			}
			position.x += B_Vx;
			position.y -= (B_Vy + grav);
			B_Vy -= grav;
		}
	}

	if (App->Boosters->slowtime == true) {
		if (App->Boosters->stoptime != true) {
			if (B_Vy > 4.8f)
			{
				B_Vy = 4.5f;
			}
			position.x += B_Vx;
			position.y -= (B_Vy + grav);
			B_Vy = grav;
		}
	}
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
		App->enemies->AddEnemy(Enemy_Type::Med_Ball2, position.x - 10, position.y);
		
		
	}
}