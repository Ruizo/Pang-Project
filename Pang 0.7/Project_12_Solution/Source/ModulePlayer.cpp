#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleBoosters.h"

#include "ModuleEnemies.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel4.h"
#include "SceneLevel5.h"
#include "SceneLevel6.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	name = "player";

	// idle animation - just one sprite
	idleAnim.PushBack({ 19, 145, 25, 32 });

	// move upwards
	upAnim.PushBack({ 0, 0, 25, 32 });
	upAnim.PushBack({ 0, 0, 25, 32 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;

	// Move right

	rightAnim.PushBack({ 19,1,30,32 });
	rightAnim.PushBack({ 53,1,30,32 });
	rightAnim.PushBack({ 87,1,30,32 });
	rightAnim.PushBack({ 121,1,30,32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({ 149,34,30,32 });
	leftAnim.PushBack({ 115,34,30,32 });
	leftAnim.PushBack({ 81,34,30,32 });
	leftAnim.PushBack({ 13,34,30,32 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	// Shoot
	shootAnim.PushBack({ 51,145,30,32 });
	shootAnim.loop = false;
	shootAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	bool ret = true;

	if (start == true) {
		LOG("Loading player textures");

		livess = App->textures->Load("Assets/Sprites/lives.png");
		

		texture = App->textures->Load("Assets/Sprites/player.png");
		currentAnimation = &idleAnim;

		laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
		explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

		position.x = 200;
		position.y = 168;

		

		// TODO 4: Retrieve the player when playing a second time
		if (destroyed == true)
		{
			destroyed = false;
		}

		collider = App->collisions->AddCollider({ position.x, position.y, 30, 32 }, Collider::Type::PLAYER, this);
		//App->live->AddParticle(App->live->Plife, 13, 224, Collider::Type::NONE);
		++activeColliders; ++totalColliders;

		char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
		scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
		++activeFonts; ++totalFonts;
		start = false;
	}

	return ret;
}

Update_Status ModulePlayer::Update()
{
	if (doubleshot == true) {
		tempDW++;

		LOG("%d", tempDW);
		if (tempDW == 300) {
			
			doubleshot = false;
			tempDW = 0;
		}
	}
	
	GamePad& pad = App->input->pads[0];
	if (!debug) {
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && stairs == true /*|| pad.l_x < 0.0f*/)
		{
			position.y -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
			if (position.y == 150) {
				stairs = false;
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT /*|| pad.l_x < 0.0f*/)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT /*|| pad.l_x > 0.0f*/)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}
		
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && (shoot) /*|| pad.a == true*/)
		{

			if (currentAnimation != &shootAnim)
			{
				shootAnim.Reset();
				currentAnimation = &shootAnim;
			}
			if (doubleshot == false) {
				App->particles->AddParticle(App->particles->laser, position.x + 10, position.y + 24, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shoot = false;
			}

			if (doubleshot == true) {
				
				
				App->particles->AddParticle(App->particles->laser, position.x + 10, position.y + 24, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shoots++;
				if (shoots == 2) {
					shoot = false;
				}
				
		

				
			}
		}
				if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE)
		{
			currentAnimation = &idleAnim;
			//position.y = 168;
		}

		if (godmode != true) {
			collider->SetPos(position.x, position.y);

			currentAnimation->Update();

		}
		else if (godmode = true) {
			collider->SetPos(10000, 10000);
			tempIn++;
			if (tempIn == 300) {
				godmode = false;
				tempIn = 0;
			}
		}

		if (destroyed)
		{
			destroyedCountdown--;
			if (destroyedCountdown <= 0)
				return Update_Status::UPDATE_STOP;
		}

		if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN && (!debug))
		{
			debug = true;
		}

	}

	if (debug) {

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.y -= 5;
			if (currentAnimation != &shootAnim)
			{
				leftAnim.Reset();
				currentAnimation = &shootAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			position.y += 5;
			if (currentAnimation != &shootAnim)
			{
				leftAnim.Reset();
				currentAnimation = &shootAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= 5;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += 5;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && (shoot))
		{
			if (currentAnimation != &shootAnim)
			{
				shootAnim.Reset();
				currentAnimation = &shootAnim;
			}
			shoot = false;
			App->particles->AddParticle(App->particles->laser, position.x + 10, position.y + 24, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);



		}


		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE)
		{
			currentAnimation = &idleAnim;
			//position.y = 168;
		}

		collider->SetPos(10000, 10000);

		currentAnimation->Update();

		if (App->input->keys[SDL_SCANCODE_H] == Key_State::KEY_DOWN && (debug))
		{
			debug = false;
		}

		if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN && (debug))
		{
			App->enemies->AddEnemy(Enemy_Type::Big_Ball, position.x + 10, position.y);
		}

		if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN && (debug))
		{
			App->enemies->AddEnemy(Enemy_Type::Med_Ball, position.x + 10, position.y);
		}

		if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN && (debug))
		{
			App->enemies->AddEnemy(Enemy_Type::Small_Ball2, position.x + 10, position.y);
		}

		if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN && (debug))
		{
			App->enemies->CleanUp();
		}

		if (App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_DOWN && (debug))
		{
			App->player->Disable();
			App->fade->FadeToBlack(this, (Module*)App->sceneOver, 90);
		}

		if (App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_DOWN && (debug))
		{

			App->Boosters->AddBooster(Booster_Type::INVINCIBLE, position.x + 10, position.y);
		}
	}
	/*// If no up/down movement detected, set the current animation back to idle
	if (pad.enabled)
	{
		if (pad.l_x == 0.0f && pad.l_y == 0.0f)
			currentAnimation = &idleAnim;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	// Switch gamepad debug info
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debugGamepadInfo = !debugGamepadInfo;*/

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
		if (lives == 2) {
			App->render->Blit(livess, livepo, 230, NULL);
			App->render->Blit(livess, livepo + 17, 230, NULL);
			App->render->Blit(livess, livepo + 34, 230, NULL);
		}
		else if (lives == 1) {
			App->render->Blit(livess, livepo, 230, NULL);
			App->render->Blit(livess, livepo + 17, 230, NULL);
		}
		else if (lives == 0) {
			App->render->Blit(livess, livepo, 230, NULL);
		}
	}

	// Draw UI (score) --------------------------------------
    sprintf_s(scoreText, 10, "%7d", score);

	App->fonts->BlitText(43, 226, scoreFont, scoreText);


	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	// TODO 1: Remove ALL remaining resources. Update resource count properly

	App->textures->Unload(texture);
	--totalTextures;

	App->audio->UnloadFx(laserFx);
	--totalFx;

	App->audio->UnloadFx(explosionFx);
	--totalFx;

	/*App->collisions->RemoveCollider(collider);
	--totalColliders;*/

	App->fonts->UnLoad(scoreFont);
	--totalFonts;

	return true;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		if (c2->type == Collider::Type::WALL4) {
			position.x -= 1;
		}
		else if (c2->type == Collider::Type::STAIRS) {
			stairs = true;

			if (position.y == 120) {
				stairs = false;
			}
		}
		else if (c2->type == Collider::Type::ELEVATOR) {
			position.y += 2;
		}
		else if (c2->type == Collider::Type::NONE) {
			stairs = false;
		}
		else if (c2->type == Collider::Type::WALL3) {
			position.x += 1;
		}
		else if (c2->type == Collider::Type::ENEMY) {
			if (!debug) {
				
				if (lives == 0) {
					App->player->CleanUp();
					App->enemies->CleanUp();
					App->fade->FadeToBlack(this, (Module*)App->sceneOver, 90);
				
				}
				else if (lives != 0) {
					start = true;
					lives--;
					if (level1 == true) {
						App->player->CleanUp();
						App->enemies->CleanUp();
						App->fade->FadeToBlack(this, (Module*)App->death, 90);
					
					}
					else if (level2 == true) {
						App->player->CleanUp();
						App->enemies->CleanUp();
						App->fade->FadeToBlack(this, (Module*)App->death, 90);
					}
					else if (level3 == true) {
						App->player->CleanUp();
						App->enemies->CleanUp();
						App->fade->FadeToBlack(this, (Module*)App->death, 90);
					}
					else if (level4 == true) {
						App->player->CleanUp();
						App->enemies->CleanUp();
						App->fade->FadeToBlack(this, (Module*)App->death, 90);
					}
					else if (level5 == true) {
						App->player->CleanUp();
						App->enemies->CleanUp();
						App->fade->FadeToBlack(this, (Module*)App->death, 90);
					}
					else if (level6 == true) {
						App->player->CleanUp();
						App->enemies->CleanUp();
						App->fade->FadeToBlack(this, (Module*)App->death, 90);
					}
			
				}


			}
		}
	}
}