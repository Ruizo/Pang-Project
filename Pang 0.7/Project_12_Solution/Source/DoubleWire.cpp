#include "Booster.h"
#include "DoubleWire.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "Module.h"


DoubleWire::DoubleWire(int x, int y) : Booster(x, y)
{

	flyAnim.PushBack({ 47,63,15,15 });
	flyAnim.loop = false;

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 16 }, Collider::Type::BOOSTERS, (Module*)App->Boosters);
}

void DoubleWire::Update()
{
	
		position.y = position.y + 1;



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Booster::Update();
}

void DoubleWire::OnCollision(Collider* c2)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
	if (c2->type == Collider::Type::PLAYER) {
		powerup = true;
		
		App->player->doubleshot = true;
	}

}