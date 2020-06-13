#include "PowerWireP.h"

#include "Collider.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "PowerWire.h"

PowerWireP::PowerWireP()
{
	position.SetToZero();
	speed.SetToZero();
}

PowerWireP::PowerWireP(const PowerWireP& p) : anim(p.anim), position(p.position), speed(p.speed),
frameCount(p.frameCount), lifetime(p.lifetime)
{

}

PowerWireP::~PowerWireP()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool PowerWireP::Update()
{
	bool ret = true;
	frameCount++;

	// The PowerWireP is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the PowerWireP has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the PowerWireP is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen
		position.x += speed.x;
		position.y += speed.y;


		if (collider != nullptr && App->player->VulcanB == true) {
			collider->SetPos(position.x, position.y);
		}
		else if (collider != nullptr && App->player->powerwireB == true) 
		{			
			if (App->powerwireB->yes != true) {
				collider->SetPos(position.x, position.y);
				collider->rect.h -= speed.y;
			}
		}else if (collider != nullptr && App->player->powerwireB == false && App->player->VulcanB == false) {
			collider->SetPos(position.x, position.y);
			collider->rect.h -= speed.y;
		}
	}

	return ret;
}

void PowerWireP::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}