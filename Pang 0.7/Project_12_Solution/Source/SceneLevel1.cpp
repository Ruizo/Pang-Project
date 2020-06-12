#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleBoosters.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	name = "level 1";
}

SceneLevel1::~SceneLevel1()
{
	
}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->player->level1 = true;
	App->player->level2 = false;
	App->player->level3 = false;
	App->player->level4 = false;
	App->player->level5 = false;
	App->player->level6 = false;



	App->collisions->Enable();
	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	App->collisions->AddCollider({ 0, 0, 384, 9 }, Collider::Type::WALL1);		//UpWall
	App->collisions->AddCollider({ 0, 200, 384, 9 }, Collider::Type::WALL2);	//DownWall
	App->collisions->AddCollider({ 0, 8, 8, 192 }, Collider::Type::WALL3);	    //RightWall
	App->collisions->AddCollider({ 376, 9, 8, 192 }, Collider::Type::WALL4);	//LeftWall

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::Big_Ball, 50, 80);
	App->Boosters->AddBooster(Booster_Type::DOUBLEWIRE, 100, 80);
	App->Boosters->AddBooster(Booster_Type::INVINCIBLE, 300, 80);
	App->Boosters->AddBooster(Booster_Type::STOPTIME, 200, 80);
	App->Boosters->AddBooster(Booster_Type::SLOWTIME, 250, 80);

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

Update_Status SceneLevel1::Update()
{


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->fonts->BlitText(17, 215, scoreFont, "player_1");
	App->fonts->BlitText(273, 215, scoreFont, "player_2");
	App->fonts->BlitText(171, 215, scoreFont, "mt.fuji");
	App->fonts->BlitText(160, 229, scoreFont, "1_1 stage");


	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->sceneLevel_1->Disable();
	App->collisions->CleanUp();

	

	return true;
}