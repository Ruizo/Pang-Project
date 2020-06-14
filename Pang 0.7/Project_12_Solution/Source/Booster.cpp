#include "Booster.h"

#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Module.h"


Booster::Booster(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Booster::~Booster()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Booster::GetCollider() const
{
	return collider;
}

void Booster::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Booster::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Booster::OnCollision(Collider* collider)
{
}