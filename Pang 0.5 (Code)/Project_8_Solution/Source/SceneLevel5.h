#ifndef __SCENE_LEVEL5_H__
#define __SCENE_LEVEL5_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel5 : public Module
{
public:
	//Constructor
	SceneLevel5(bool startEnabled);

	//Destructor
	~SceneLevel5();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
};

#endif