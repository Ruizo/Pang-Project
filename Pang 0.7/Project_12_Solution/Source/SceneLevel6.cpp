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

	App->player->doubleshot = false;
	App->Boosters->slowtime = false;
	App->player->powerwireB = false;
	App->Boosters->stoptime = false;

	App->collisions->Enable();
	bgTexture = App->textures->Load("Assets/Sprites/background_6.png");
	App->audio->PlayMusic("Assets/Music/stage2.ogg", 1.0f);

	App->collisions->AddCollider({ 0, 0, 384, 9 }, Collider::Type::WALL1);		//UpWall
	App->collisions->AddCollider({ 0, 200, 384, 9 }, Collider::Type::WALL2);	//DownWall
	App->collisions->AddCollider({ 0, 8, 8, 192 }, Collider::Type::WALL3);	    //RightWall
	App->collisions->AddCollider({ 376, 9, 8, 192 }, Collider::Type::WALL4);	//LeftWall

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 30, 90);
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 100, 90);

	//Platforms ---
	App->enemies->AddEnemy(Enemy_Type::BreakablePlatform, SCREEN_WIDTH / 2 - 7, 60);
	App->enemies->AddEnemy(Enemy_Type::BreakablePlatform, SCREEN_WIDTH / 4 - 7, 60);
	App->enemies->AddEnemy(Enemy_Type::BreakablePlatform, 3 * SCREEN_WIDTH / 4 - 7, 60);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->Boosters->Enable(); 

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

	App->fonts->BlitText(17, 215, scoreFont, "player_1");
	App->fonts->BlitText(273, 215, scoreFont, "player_2");
	App->fonts->BlitText(171, 215, scoreFont, "mt. keirin");
	App->fonts->BlitText(160, 229, scoreFont, "2_3 stage");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel6::CleanUp()
{

	App->player->Disable();
	App->enemies->Disable();
	App->Boosters->Disable();
	App->sceneLevel_6->Disable();
	App->collisions->CleanUp();
	return true;
}