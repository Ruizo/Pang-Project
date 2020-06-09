#include "ModuleLives.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

Lives::Lives(bool startEnabled) : Module(startEnabled)
{

}

Lives::~Lives()
{

}

// Load assets
bool Lives::Start()
{
	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/live.png");
		
	position.x = 200;
	position.y = 50;

	// TODO 4: Retrieve the player when playing a second time
	
	return ret;
}

Update_Status Lives::Update()
{
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Lives::PostUpdate()
{
	

	return Update_Status::UPDATE_CONTINUE;
}