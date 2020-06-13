#include "SceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "ModuleCollisions.h"

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{

}

SceneWin::~SceneWin()
{

}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Win.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneWin::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	App->collisions->Disable();
	App->sceneLevel_1->Disable();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}