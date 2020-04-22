#include "Menu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleCollisions.h"


#include <SDL\include\SDL_scancode.h>

Menu::Menu()
{

}

Menu::~Menu() 
{

}

// Load assets
bool Menu::Start()
{
	bool back = true;

	bgTexture = App->textures->Load("Assets/Menu.png");
	//App->audio->PlayMusic("Assets/Sound/Sounds_Gameplay/Title.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return back;
}


// Update: draw background
update_status Menu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}