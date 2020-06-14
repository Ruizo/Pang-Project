#include "Booster.h"
#include "VulcanB.h"
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
#include "Vulcan.h"


VulcanB::VulcanB(int x, int y) : Booster(x, y)
{

	flyAnim.PushBack({ 86, 65, 16, 13 });
	flyAnim.loop = false;

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 16 }, Collider::Type::BOOSTERS, (Module*)App->Boosters);
}

void VulcanB::Update()
{

	position.y = position.y + 1;



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Booster::Update();
}

void VulcanB::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER) {
		App->player->VulcanB = true;
		App->vulcanB->Enable();
		App->player->doubleshot = false;
		App->player->powerwireB = false;
	}
}