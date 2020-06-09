#include "SceneLevel4.h"

#include "Enemy.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

SceneLevel4::SceneLevel4(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel4::~SceneLevel4()
{

}

// Load assets
bool SceneLevel4::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->collisions->Enable();
	bgTexture = App->textures->Load("Assets/Sprites/background_4.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	App->collisions->AddCollider({ 0, 0, 384, 9 }, Collider::Type::WALL1);		//UpWall
	App->collisions->AddCollider({ 0, 200, 384, 9 }, Collider::Type::WALL2);	//DownWall
	App->collisions->AddCollider({ 184, 152, 16, 3 }, Collider::Type::WALL2);
	App->collisions->AddCollider({ 192, 155, 8, 32 }, Collider::Type::WALL3);
	App->collisions->AddCollider({ 0, 8, 8, 192 }, Collider::Type::WALL3);
	App->collisions->AddCollider({ 184, 155, 8, 32 }, Collider::Type::WALL4);
	App->collisions->AddCollider({ 376, 9, 8, 192 }, Collider::Type::WALL4);	//LeftWall

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 50, 80);

	//Platforms ---

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel4::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel4::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel4::CleanUp()
{

	App->player->Disable();
	App->enemies->Disable();

	return true;
}