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
#include "ModuleFonts.h"
#include "ModuleBoosters.h"

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

	App->player->level1 = false;
	App->player->level2 = false;
	App->player->level3 = false;
	App->player->level4 = true;
	App->player->level5 = false;
	App->player->level6 = false;




	App->collisions->Enable();
	bgTexture = App->textures->Load("Assets/Sprites/background_4.png");
	App->audio->PlayMusic("Assets/Music/stage2.ogg", 1.0f);

	App->collisions->AddCollider({ 0, 0, 384, 9 }, Collider::Type::WALL1);		//UpWall
	App->collisions->AddCollider({ 0, 200, 384, 9 }, Collider::Type::WALL2);	//DownWall
	App->collisions->AddCollider({ 184, 152, 16, 3 }, Collider::Type::WALL2);
	App->collisions->AddCollider({ 192, 155, 8, 32 }, Collider::Type::WALL3);
	App->collisions->AddCollider({ 0, 8, 8, 192 }, Collider::Type::WALL3);
	App->collisions->AddCollider({ 184, 155, 8, 32 }, Collider::Type::WALL4);
	App->collisions->AddCollider({ 376, 9, 8, 192 }, Collider::Type::WALL4);



	App->collisions->AddCollider({ 168, 140, 8, 40 }, Collider::Type::STAIRS);
	App->collisions->AddCollider({ 210, 140, 8, 40 }, Collider::Type::STAIRS);



	App->collisions->AddCollider({ 128, 114, 8, 53 }, Collider::Type::ELEVATOR);
	App->collisions->AddCollider({ 250, 114, 8, 53 }, Collider::Type::ELEVATOR);




	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 50, 80);

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

Update_Status SceneLevel4::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel4::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->fonts->BlitText(17, 215, scoreFont, "player_1");
	App->fonts->BlitText(273, 215, scoreFont, "player_2");
	App->fonts->BlitText(171, 215, scoreFont, "mt. keirin");
	App->fonts->BlitText(160, 229, scoreFont, "2_1 stage");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel4::CleanUp()
{

	App->player->Disable();
	App->enemies->Disable();
	App->sceneLevel_4->Disable();
	App->collisions->CleanUp();

	return true;
}