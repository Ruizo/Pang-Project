#include "SceneLevel2.h"

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

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	App->player->score = App->player->totalscore;
	LOG("Loading background assets");

	bool ret = true;

	App->player->level1 = false;
	App->player->level2 = true;
	App->player->level3 = false;
	App->player->level4 = false;
	App->player->level5 = false;
	App->player->level6 = false;

	App->player->doubleshot = false;




	App->collisions->Enable();
	bgTexture = App->textures->Load("Assets/Sprites/background_2.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);


	App->collisions->AddCollider({ 0, 0, 384, 9 }, Collider::Type::WALL1);		//UpWall
	App->collisions->AddCollider({ 0, 200, 384, 9 }, Collider::Type::WALL2);	//DownWall
	App->collisions->AddCollider({ 0, 8, 8, 192 }, Collider::Type::WALL3);	    //RightWall
	App->collisions->AddCollider({ 376, 9, 8, 192 }, Collider::Type::WALL4);	//LeftWall

	// Enemies ---


	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 50, 80);

	//Platforms ---
	App->enemies->AddEnemy(Enemy_Type::BreakablePlatform, SCREEN_WIDTH / 2 - 31, 70);//A
	App->enemies->AddEnemy(Enemy_Type::BreakablePlatform, SCREEN_WIDTH / 2, 70);//B

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

Update_Status SceneLevel2::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->fonts->BlitText(17, 215, scoreFont, "player_1");
	App->fonts->BlitText(273, 215, scoreFont, "player_2");
	App->fonts->BlitText(171, 215, scoreFont, "mt.fuji");
	App->fonts->BlitText(160, 229, scoreFont, "1_2 stage");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->Boosters->Disable();
	App->sceneLevel_2->Disable();	
	App->collisions->CleanUp();
	return true;
}