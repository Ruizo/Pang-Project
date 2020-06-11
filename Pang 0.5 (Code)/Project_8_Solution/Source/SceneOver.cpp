#include "SceneOver.h"

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

SceneOver::SceneOver(bool startEnabled) : Module(startEnabled)
{

}

SceneOver::~SceneOver()
{

}

// Load assets
bool SceneOver::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Over.png");
	App->audio->PlayMusic("Assets/Music/pornhubintro.mp3", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneOver::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{			
		if (App->player->level1)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		}
		if (App->player->level2)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
		}
		if (App->player->level3)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3, 90);
		}
		if (App->player->level4)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
		}
		if (App->player->level5)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_5, 90);
		}
		if (App->player->level6)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_6, 90);
		}
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
Update_Status SceneOver::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	return Update_Status::UPDATE_CONTINUE;
}