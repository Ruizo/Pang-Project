#include "SceneLevel6.h"

#include "Enemy.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "ModuleBoosters.h"

SceneLevel6::SceneLevel6(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel6::~SceneLevel6()
{

}

// Load assets
bool SceneLevel6::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->player->level1 = false;
	App->player->level2 = false;
	App->player->level3 = false;
	App->player->level4 = false;
	App->player->level5 = false;
	App->player->level6 = true;




	App->collisions->Enable();
	bgTexture = App->textures->Load("Assets/Sprites/background_6.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	App->collisions->AddCollider({ 0, 0, 384, 9 }, Collider::Type::WALL1);		//UpWall
	App->collisions->AddCollider({ 0, 200, 384, 9 }, Collider::Type::WALL2);	//DownWall
	App->collisions->AddCollider({ 0, 8, 8, 192 }, Collider::Type::WALL3);	    //RightWall
	App->collisions->AddCollider({ 376, 9, 8, 192 }, Collider::Type::WALL4);	//LeftWall

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 50, 80);
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 120, 80);

	//Platforms ---


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyzA" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	++activeFonts; ++totalFonts;

	return ret;
}

Update_Status SceneLevel6::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel6::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel6::CleanUp()
{

	App->player->Disable();
	App->enemies->Disable();

	return true;
}