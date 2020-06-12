#include "ModuleCollisions.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"


ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	name = "collisions";

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL1][Collider::Type::WALL1] = false;
	matrix[Collider::Type::WALL1][Collider::Type::WALL2] = false;
	matrix[Collider::Type::WALL1][Collider::Type::WALL3] = false;
	matrix[Collider::Type::WALL1][Collider::Type::WALL4] = false;
	matrix[Collider::Type::WALL1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL1][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL1][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL1][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::WALL1][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::WALL1][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::WALL1][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::WALL1][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::WALL1][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::WALL2][Collider::Type::WALL1] = false;
	matrix[Collider::Type::WALL2][Collider::Type::WALL2] = false;
	matrix[Collider::Type::WALL2][Collider::Type::WALL3] = false;
	matrix[Collider::Type::WALL2][Collider::Type::WALL4] = false;
	matrix[Collider::Type::WALL2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL2][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL2][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WALL2][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::WALL2][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::WALL2][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::WALL2][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::WALL2][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::WALL2][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::BOOSTERS][Collider::Type::WALL2] = true;
	matrix[Collider::Type::BOOSTERS][Collider::Type::PLAYER] = true;


	matrix[Collider::Type::WALL3][Collider::Type::WALL1] = false;
	matrix[Collider::Type::WALL3][Collider::Type::WALL2] = false;
	matrix[Collider::Type::WALL3][Collider::Type::WALL3] = false;
	matrix[Collider::Type::WALL3][Collider::Type::WALL4] = false;
	matrix[Collider::Type::WALL3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL3][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL3][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL3][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::WALL3][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::WALL3][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::WALL3][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::WALL3][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::WALL3][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::WALL4][Collider::Type::WALL1] = false;
	matrix[Collider::Type::WALL4][Collider::Type::WALL2] = false;
	matrix[Collider::Type::WALL4][Collider::Type::WALL3] = false;
	matrix[Collider::Type::WALL4][Collider::Type::WALL4] = false;
	matrix[Collider::Type::WALL4][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL4][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL4][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL4][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::WALL4][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::WALL4][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::WALL4][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::WALL4][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::WALL4][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL4] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOOSTERS] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STAIRS] = true;


	matrix[Collider::Type::ENEMY][Collider::Type::WALL1] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::WALL2] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::WALL3] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::WALL4] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::BPLATFORMUp] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::BPLATFORMDown] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::BPLATFORMRight] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::BPLATFORMLeft] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::BPLATFORM] = true;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL1] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL2] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL3] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL4] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BPLATFORM] = true;

	matrix[Collider::Type::BPLATFORMUp][Collider::Type::WALL1] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::WALL2] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::WALL3] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::WALL4] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::BPLATFORMUp][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::BPLATFORMDown][Collider::Type::WALL1] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::WALL2] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::WALL3] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::WALL4] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::BPLATFORMDown][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::BPLATFORMRight][Collider::Type::WALL1] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::WALL2] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::WALL3] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::WALL4] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::BPLATFORMRight][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::WALL1] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::WALL2] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::WALL3] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::WALL4] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::BPLATFORMLeft][Collider::Type::BOOSTERS] = false;

	matrix[Collider::Type::BPLATFORM][Collider::Type::WALL1] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::WALL2] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::WALL3] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::WALL4] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BPLATFORM][Collider::Type::BPLATFORMUp] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::BPLATFORMDown] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::BPLATFORMRight] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::BPLATFORMLeft] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::BPLATFORM] = false;
	matrix[Collider::Type::BPLATFORM][Collider::Type::BOOSTERS] = false;


}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			--colliderCount;

		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);

				/* if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);

				else if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);*/
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 150;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL1: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::WALL2: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::WALL3: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::WALL4: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::BPLATFORM:
			App->render->DrawQuad(colliders[i]->rect, 127, 0, 255, alpha);
			break;
		case Collider::Type::BPLATFORMUp: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BPLATFORMDown: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BPLATFORMRight: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BPLATFORMLeft: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BOOSTERS: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		
		case Collider::Type::STAIRS:
			App->render->DrawQuad(colliders[i]->rect, 150, 200, 50, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			++colliderCount;
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			--colliderCount;
		}
	}
}
