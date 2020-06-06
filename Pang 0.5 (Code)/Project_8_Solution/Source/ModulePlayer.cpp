#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
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
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/player.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	MovePlayer(200, 0);

	// TODO 4: Retrieve the player when playing a second time
	if (destroyed == true)
	{
		destroyed = false;
	}

	collider = App->collisions->AddCollider({ position.x, position.y, 30, 32 }, Collider::Type::PLAYER, this);

	return ret;
}



Update_Status ModulePlayer::Update()
{
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{

		if (currentAnimation != &shootAnim)
		{
			shootAnim.Reset();
			currentAnimation = &shootAnim;
		}
		App->particles->AddParticle(App->particles->laser, position.x + 12, position.y + 20, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE)
	{
		currentAnimation = &idleAnim;
		position.y = 168;
	}

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::MovePlayer(int x, int y) {
	position.x = x;
	position.y = y;

}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		if (c2->type == Collider::Type::WALL4) {
			position.x -= 1;
		}
		else if(c2->type == Collider::Type::WALL3){
			position.x += 1;
		}
		else if (c2->type == Collider::Type::ENEMY) {
			App->player->Disable();
			App->fade->FadeToBlack(this, (Module*)App->sceneOver, 90);
		}
	}
	

}

