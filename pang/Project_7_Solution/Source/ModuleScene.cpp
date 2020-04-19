#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png");
	//App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//Walls colliders
	App->collisions->AddCollider({ 0, 0, 384, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 231, 384, 9 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 10, 9, 221 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 375, 10, 9, 221 }, Collider::Type::WALL);
	

	// TODO 1: Add a new wave of red birds
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 735, 120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 750, 120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 775, 120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 790, 120);

	// TODO 2: Add a new wave of brown cookies
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 890, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::MECH, 900, 195);


	return ret;
}

update_status ModuleScene::Update()
{
	//App->render->camera.x += 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}