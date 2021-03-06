#include "Booster.h"
#include "StopTime.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "Module.h"
#include "Particle.h"
#include "Balls.h"
#include "ModuleBoosters.h"


StopTime::StopTime(int x, int y) : Booster(x, y)
{

	flyAnim.PushBack({ 8, 102, 16, 16 });
	flyAnim.loop = false;

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 16 }, Collider::Type::BOOSTERS, (Module*)App->Boosters);
}

void StopTime::Update()
{

	position.y = position.y + 1;



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Booster::Update();
}

void StopTime::OnCollision(Collider* c2)
{

	if (c2->type == Collider::Type::PLAYER) {
		App->Boosters->stoptime = true;
	}
}