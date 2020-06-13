#include "Death.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel4.h"
#include "SceneLevel5.h"
#include "SceneLevel6.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Death::Death(bool startEnabled) : Module(startEnabled)
{

}

Death::~Death()
{

}

// Load assets
bool Death::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	//bgTexture = App->textures->Load("Assets/Sprites/Over.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status Death::Update()
{
	App->player->score = 0;
	
		if (App->player->level1 == true) {
	
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);

		}
		else if (App->player->level2 == true) {
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
		}
		else if (App->player->level3 == true) {
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3, 90);
		}
		else if (App->player->level4 == true) {
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
		}
		else if (App->player->level5 == true) {
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_5, 90);
		}
		else if (App->player->level6 == true) {
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_6, 90);
		}
	
	
	App->collisions->Disable();
	App->sceneLevel_1->Disable();
	App->sceneLevel_2->Disable();
	App->sceneLevel_3->Disable();
	App->sceneLevel_4->Disable();
	App->sceneLevel_5->Disable();
	App->sceneLevel_6->Disable();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Death::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}