#include "Booster.h"
#include "Invincibility.h"
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


Invincibility::Invincibility(int x, int y) : Booster(x, y)
{

	flyAnim.PushBack({ 8, 372, 10, 8 });
	flyAnim.PushBack({ 26, 368, 14, 12 });
	flyAnim.PushBack({ 48, 366, 16, 13 });
	flyAnim.PushBack({ 72, 366, 16, 13 });
	flyAnim.PushBack({ 96, 366, 16, 14 });
	flyAnim.PushBack({ 120, 366, 15, 13 });
	flyAnim.PushBack({ 144, 366, 15, 13 });
	flyAnim.PushBack({ 168, 368, 14, 12 });	
	flyAnim.loop = true;

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 16 }, Collider::Type::BOOSTERS, (Module*)App->Boosters);
}

void Invincibility::Update()
{

	position.y = position.y + 1;



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Booster::Update();
}

void Invincibility::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER) {
		App->player->godmode = true;

	}
}