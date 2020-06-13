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


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneOver::Update()
{
	App->player->score = 0;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{			
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);		
	}
	App->collisions->Disable();
	App->sceneLevel_1->Disable();
	App->sceneLevel_2->Disable();
	App->sceneLevel_3->Disable();
	App->sceneLevel_4->Disable();
	App->sceneLevel_5->Disable();
	App->sceneLevel_6->Disable();
	App->player->lives = 2;
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneOver::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	return Update_Status::UPDATE_CONTINUE;
}