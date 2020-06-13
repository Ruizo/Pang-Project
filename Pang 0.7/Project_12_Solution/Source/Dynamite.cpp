#include "Booster.h"
#include "Dynamite.h"
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
#include "ModuleEnemies.h"


Dynamite::Dynamite(int x, int y) : Booster(x, y)
{

	flyAnim.PushBack({ 88, 105, 15, 13 });
	flyAnim.PushBack({ 111, 105, 16, 15 });
	flyAnim.PushBack({ 135, 105, 15, 16 });
	flyAnim.loop = true;

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 16 }, Collider::Type::BOOSTERS, (Module*)App->Boosters);
}

void Dynamite::Update()
{

	position.y = position.y + 1;



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Booster::Update();
}

void Dynamite::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER) {
		
	}
}